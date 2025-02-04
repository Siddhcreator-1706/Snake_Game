# 🐍 Snake Game 🎮
## 🎮 Description
This is a **classic Snake game** implemented in C++ using the console. The game features a simple interface where the player controls a snake to eat food, grow in size, and avoid colliding with itself. The game wraps around the screen edges, and the player can choose from different difficulty levels.
The game supports real-time keyboard input and runs smoothly in the command line.

## 🎯 Features
- 🚀 **Real-time movement** using keys (`W S A D`)
- 🍎 **Food spawning** increases the snake’s length and **score tracking**.
- ⛔ **Collision detection** (Walls & Self-collision)
- 🕹️ **Smooth controls** with **non-blocking input**

---

## 🛠️ Installation Steps
1️⃣ **Clone the repository:**  
```sh
 git clone https://github.com/Siddhcreator-1706/Snake_Game.git
```
2️⃣ **Navigate to the project directory:**  
```sh
 cd Snake_Game
```
3️⃣ **Compile the game:**  
```sh
 g++ snake_game.cpp -o snake_game.exe
```
4️⃣ **Run the game:**  
```sh
 ./snake_game.exe
```

## 🎯 How to Play
1️⃣ Run the program in console.  
2️⃣ Enter your **player name** when prompted.  
3️⃣ Choose a difficulty level:  
   - 🟢 `1`: **Easy**  
   - 🟡 `2`: **Medium** *(default)*  
   - 🔴 `3`: **Hard**  
4️⃣ Control the snake using the following keys:  
   - ⬆️ `W` - Move Up  
   - ⬅️ `A` - Move Left  
   - ⬇️ `S` - Move Down  
   - ➡️ `D` - Move Right  
   - ❌ `X` - Quit the game  
5️⃣ The snake must **eat the food** (#) to grow and earn points.  
6️⃣ Avoid running into yourself; otherwise, the game will end.  
7️⃣ Once the game is **over**, press 🔄 `R` to restart or any other key to exit.  

## 🔍 Notes
- The game uses the `_kbhit()` function from `conio.h` for **non-blocking keyboard input**.  
- The `Sleep(dfc);` function controls the **game speed** based on difficulty.  
- The **console cursor is hidden** for a cleaner display.  

## 🚀 Future Improvements
🚧 **Add a graphical user interface (GUI) for better visuals.**  
🏆 **Implement a high-score leaderboard.**  
🕹️ **Introduce new obstacles and power-ups.**  
👥 **Allow multiplayer mode.**  

🎉 **Enjoy the game!** 🐍

