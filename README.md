# 🧠 Neural Network From Scratch with Real-Time Visualization (C + Allegro)

![C](https://img.shields.io/badge/C-99-blue.svg)
![Allegro](https://img.shields.io/badge/Allegro-5.x-red.svg)  

![License](https://img.shields.io/badge/license-MIT-green.svg)  
![Contributions](https://img.shields.io/badge/contributions-welcome-orange.svg)  

## 📝 Project Description  
Welcome to my first big project : **Neural Network From Scratch** 🧠 !  
This project implements a simple neural network from scratch in C. It learns to approximate basic target functions through supervised learning, using gradient descent and backpropagation.  

What makes this project unique is its **real-time graphical visualization** using the Allegro graphics library : We are able to see the difference between targets and outputs, graph for the loss and visualisation of the network🕸️.

---

# 🚀 Features
  🧩 Fully custom neural network implementation in C (no external ML libraries)

## Example Outputs  
  ![NN image](Images/NN_display_in_action.png)
  📈 Live training visualization, including:

    - 🔵 Left side: graph showing target values vs. predicted values

    - 🧮 Top-right: automatic graph of mean error over iterations

    - 🕸️ Bottom: dynamic visualization of the neural network itself (node color reflects activation values)

  🛠️ Simple training on arbitrary datasets (hardcoded on donnees.txt)  

---

## ⚙️ How it works
- 

---

## 📂 Repository structure  
```bash
├── img/           # For the README.md
├── text/          # Training corpora (Victor Hugo, Harry Potter, …)
├── Bigram.py      # Bigram model + first experiments  
├── LICENSE
├── README.md
├── Transformer.py # Full Transformer implementation  
```

---
## 💻 Run it on Your PC  
Clone the repository and install dependencies:  
```bash
git clone https://github.com/Thibault-GAREL/Neural_Network_from_Scratch.git
sudo apt-get update
sudo apt-get install liballegro5-dev
# It is for Linux 🐧 !
# For macOS 🍎 / Windows 🪟 , consult the official Allegro documentation.
```

---

## 📖 Inspiration / Sources  
This project is based on a basic book named "L'intelligence artificielle pour les dévellopeurs" from Virginie MATHIVET.  
It just explain who work a neuron, that's all 🤯 !

---

# ✍️ P.S. 
  I coded this in 2023-2024 so it is not so well optimized ! I was a beginner. 😆
