# IdeaForge

**IdeaForge** is a powerful C++ application designed to spark creativity and generate unique ideas for game developers, writers, and artists. By selecting categories and generating random words, users can break through creative blocks and explore new concepts.

## 📌 Features

- **User-friendly Interface** – Simple category selection process
- **Random Word Generation** – Generates words based on chosen categories
- **Encourages Creative Thinking** – Helps in brainstorming new ideas
- **Ideal for Multiple Domains** – Useful for game development, writing, and artistic projects
- **Fast and Efficient** – Uses optimized algorithms for quick word selection

## 🎯 How It Works

1. The program reads predefined categories and words from a file (`word.txt`).
2. The user selects the number of categories they want to use.
3. The program randomly selects words from the chosen categories.
4. The generated words are displayed in a structured format.
5. Users can regenerate new ideas or exit the program.

## 📂 Project Structure

```
IdeaForge/
├── src/
│   ├── main.cpp        # Main program file
│   ├── FileManager.cpp # Handles file operations
│   ├── UserHandler.cpp # Manages user input
│   ├── RandomGen.cpp   # Generates random words
│
├── data/
│   ├── word.txt        # Contains categories and words
│
├── README.md           # Project documentation
├── Makefile            # Compilation instructions
```

## 🛠 Prerequisites

Ensure you have the following installed:

- **C++ Compiler** (g++ or clang++)
- **Standard C++ Libraries** (iostream, fstream, vector, string, etc.)

## 🚀 Installation & Usage

### Clone the Repository
```bash
git clone https://github.com/your-username/IdeaForge.git
cd IdeaForge
```

### Compile the Program
```bash
g++ -o ideaforge src/main.cpp
```

### Run the Program
```bash
./ideaforge
```

## 📜 Example Usage
```
Available Categories:
[0] Characters
[1] Environments
[2] Objects
[3] Art Styles
[4] Emotions

Enter the number of categories to forge an idea: 2
Enter IDs of 2 categories (0 to 4): 1 3

Generating random words...
+----------------+----------------+
| Category       | Random Word    |
+----------------+----------------+
| Environments   | Cyberpunk City |
| Art Styles    | Pixel Art      |
+----------------+----------------+
```

## 🤝 Contributing

We welcome contributions! Follow these steps:

1. **Fork the Repository** – Create a personal copy.
2. **Create a Feature Branch** – `git checkout -b feature-name`
3. **Make Your Changes** – Implement and test your changes.
4. **Commit Changes** – `git commit -m "Description of changes"`
5. **Push to GitHub** – `git push origin feature-name`
6. **Submit a Pull Request** – Request to merge into the main branch.

## 🛠 Future Enhancements

- **GUI Version** – Implement a graphical interface for easier navigation.
- **Category Customization** – Allow users to add/remove their own categories.
- **Database Integration** – Store and retrieve words from a database.
- **Machine Learning Suggestions** – Suggest word combinations based on user preferences.
- **Web Version** – Convert into a web-based application.

## 🙌 Acknowledgments

- Inspired by brainstorming techniques used in game development.
- Thanks to all contributors for their support in improving IdeaForge.
