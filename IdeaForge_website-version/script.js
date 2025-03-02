let categories = [];
let values = {};

// Load categories and values from the text file
fetch('word.txt')
    .then(response => response.text())
    .then(data => {
        parseData(data);
        displayCategories();
    })
    .catch(error => console.error('Error loading the file:', error));

// Parse the text file data
function parseData(data) {
    const lines = data.split('\n');
    let currentCategory = '';

    lines.forEach(line => {
        line = line.trim();
        if (line.startsWith('#')) {
            currentCategory = line.substring(1).trim();
            categories.push(currentCategory);
            values[currentCategory] = [];
        } else if (line.startsWith('(') && line.endsWith(')')) {
            const items = line.substring(1, line.length - 1).split(',');
            values[currentCategory] = items.map(item => item.trim());
        }
    });
}

// Display categories for selection
function displayCategories() {
    const categoryList = document.getElementById('categoryList');
    categories.forEach((category, index) => {
        const checkbox = document.createElement('input');
        checkbox.type = 'checkbox';
        checkbox.id = `category-${index}`;
        checkbox.value = category;

        const label = document.createElement('label');
        label.htmlFor = `category-${index}`;
        label.innerText = category;

        const div = document.createElement('div');
        div.className = 'category';
        div.appendChild(checkbox);
        div.appendChild(label);
        categoryList.appendChild(div);
    });

    // Add event listener for "Select All" checkbox
    const selectAllCheckbox = document.getElementById('selectAll');
    selectAllCheckbox.addEventListener('change', () => {
        const checkboxes = document.querySelectorAll('input[type="checkbox"]:not(#selectAll)');
        checkboxes.forEach(checkbox => {
            checkbox.checked = selectAllCheckbox.checked;
        });
    });
}

// Generate random words based on selected categories
document.getElementById('generateBtn').addEventListener('click', () => {
    const selectedCategories = Array.from(document.querySelectorAll('input[type="checkbox"]:checked'))
        .map(checkbox => checkbox.value);
    let numWords = parseInt(document.getElementById('numWords').value) || 1;

    if (numWords > 5) {
        alert('Maximum number of words is 5. Setting to 5.');
        numWords = 5;
    }

    const resultsDiv = document.getElementById('results');
    resultsDiv.innerHTML = ''; // Clear previous results

    // Show loading animation
    const loadingDiv = document.getElementById('loading');
    loadingDiv.style.display = 'block';

    // Simulate a delay for generating random words
    setTimeout(() => {
        selectedCategories.forEach(category => {
            const categoryValues = values[category];
            if (categoryValues && categoryValues.length > 0) { // Check if categoryValues is defined and has length
                const randomWords = [];
                for (let i = 0; i < numWords; i++) {
                    const randomIndex = Math.floor(Math.random() * categoryValues.length);
                    randomWords.push(categoryValues[randomIndex]);
                }

                const categoryResult = document.createElement('div');
                categoryResult.innerHTML = `<strong>${category}:</strong> ${randomWords.join(', ')}`;
                resultsDiv.appendChild(categoryResult);
            }
        });

        // Hide loading animation
        loadingDiv.style.display = 'none';
    }, 1000); // Simulate a 1-second delay
});

// Reset the form
document.getElementById('resetBtn').addEventListener('click', () => {
    document.getElementById('numWords').value = '';
    document.getElementById('results').innerHTML = '';
    document.querySelectorAll('input[type="checkbox"]').forEach(checkbox => {
        checkbox.checked = false;
    });
    document.getElementById('selectAll').checked = false; // Uncheck "Select All"
});