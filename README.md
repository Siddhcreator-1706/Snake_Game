# 🐍 Snake Game

Welcome to the **Snake Game**! This is a console-based snake game built using **C++** with support for both **Windows** and **Linux** systems.

## 📌 Features
- 🎮 **Smooth Movement** using keyboard controls (`W`, `A`, `S`, `D`)
- 🏆 **Scoring System**
- 🌟 **Customizable Difficulty Levels**
- 🎨 **ANSI Escape Sequences for Colors and Cursor Manipulation**
- 🔲 **Dynamic Terminal Size Adjustments**
- 🚀 **Cross-Platform Support**

## 📥 Installation
### Prerequisites
- Ensure you have a **C++ compiler** (g++ or MSVC)
- **Linux Users**: Ensure `termios.h`, `sys/ioctl.h` headers are available

### Steps
1. Clone the repository from GitHub:
   ```sh
   git clone https://github.com/Siddhcreator-1706/Snake_Game.git
   cd Snake_Game
   ```
2. Compile the game:
   ```sh
   g++ snake_game.cpp -o snake_game
   ```
   **For Windows (MinGW users)**:
   ```sh
   g++ snake_game.cpp -o snake_game.exe -static-libstdc++ -static-libgcc
   ```
3. Run the game:
   ```sh
   ./snake_game  # Linux
   snake_game.exe  # Windows
   ```

## 🎮 Usage
1. Run the game and enter your name.
2. Select a difficulty level:
   - `1` Easy
   - `2` Medium
   - `3` Hard
   - `4` Expert
3. Use `W`, `A`, `S`, `D` keys to control the snake.
4. Eat the `#` food item to grow your snake and increase your score.
5. Avoid colliding with the walls and your own body.

## 📊 Data Structure Analysis
### **Data Structures Used**
1. **Vector (`std::vector`)**
   - Stores the snake's body as a list of coordinate pairs (`std::vector<std::pair<int, int>>`).
   - Provides fast traversal and access to elements.
   - Dynamically resizable, making it easy to increase the snake's length.

2. **Enum (`enum SnakeDirection`)**
   - Defines possible movement directions: `Up`, `Down`, `Left`, and `Right`.
   - Helps in maintaining game logic for movement.

3. **Pair (`std::pair<int, int>`)**
   - Represents the position `(x, y)` of the snake's head and body segments.
   - Allows structured access to coordinates without needing a separate `struct`.

4. **Custom Classes (`Snake`, `Food`)**
   - `Snake` class:
     - Stores body segments in a `vector<pair<int, int>>`.
     - Handles movement logic and collision detection.
   - `Food` class:
     - Randomly generates food positions within game boundaries.
     - Uses `rand()` for randomization.

### **Object-Oriented Approach**
- **Encapsulation**: Snake and Food behaviors are encapsulated inside classes.
- **Modularity**: Game logic is separated into different functions.
- **Cross-Platform Compatibility**: Uses `#ifdef _WIN32` for Windows-specific code and `termios.h` for Linux.

## 🤝 Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

### Contributors
- [Siddhcreator-1706](https://github.com/Siddhcreator-1706)
- [Tanish-30-08-2006](https://github.com/Tanish-30-08-2006)
- [Keval-tech](https://github.com/Keval-tech)

## 📜 License
This project is licensed under the **MIT License**.

## 📌 Reference
Check out the project on **GitHub**: [Siddhcreator-1706/Snake_Game](https://github.com/Siddhcreator-1706/Snake_Game) 🚀

