# 🧠 Neural Network From Scratch

![C](https://img.shields.io/badge/C-99-blue.svg)
![Allegro](https://img.shields.io/badge/Allegro-5.x-red.svg)  

![License](https://img.shields.io/badge/license-MIT-green.svg)  
![Contributions](https://img.shields.io/badge/contributions-welcome-orange.svg)  

<p align="center">
  <img src="Images/Gif-neural-network.gif" alt="Logo Gif">
</p>

## 📝 Project Description  
Welcome to my first big project : **Neural Network From Scratch** 🧠 **with Real-Time Visualization (C + Allegro)** !  
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
- 🧠 Input layer: takes in data (here what is in donnees.txt)
- 🔗 Weights & biases: adjust how much each input matters
- ➕ Summation: combines inputs with weights
- 🎚️ Activation function: decides if the neuron “fires” (here we use the sigmoid fonction)
- 🏗️ Hidden layers: repeat process to learn complex patterns
- 🎯 Output layer: produces final result / prediction
- 🔄 Training: network compares result to truth, adjusts weights (backpropagation)
- 📈 Iteration: repeats until error is minimized


---

## 📂 Repository structure  
```bash
├── Images/                      # For the README.md
├── neuron_network_clear/
| ├── cmake-build-debug/
| ├── 1_fwd_propagation.c        # Forward propagation calcul
| ├── 1_fwd_propagation.h
| ├── 2_back_propagation.c       # Back propagation calcul
| ├── 2_back_propagation.h
| ├── Arial.ttf                  # Font file
| ├── CMakeLists.txt
| ├── affichage_tableau.c        # Allegro display
| ├── affichage_tableau.h
| ├── calcul.c                   # Different calcul (sigmoid / relu / MSE / etc. )
| ├── calcul.h
| ├── creator.c                  # Manage the mamory for each structure
| ├── creator.h
| ├── donnees.txt                # Here is the data the NN will learn ! You can add what ever you want.
| ├── main.c                     # Run this to start the program
| ├── structure.h
| ├── training.c                 # Do the iteration of training
| ├── training.h
├── LICENSE
├── README.md
```

---

## 💻 Run it on Your PC
Clone the repository and install dependencies:

```bash
# Clone the repository
git clone https://github.com/Thibault-GAREL/Neural_Network_from_Scratch.git
cd Neural_Network_from_Scratch

# Install dependencies (Linux 🐧)
sudo apt-get update
sudo apt-get install -y git cmake liballegro5-dev

# For macOS 🍎 / Windows 🪟, consult the official Allegro documentation:
# https://liballeg.org/

# Build the project
mkdir build && cd build
cmake .. || { echo "CMake failed. Check dependencies."; exit 1; }
make || { echo "Build failed. Check errors above."; exit 1; }

# Run the project (replace with the actual binary name)
./YourBinaryName
```

---

## 🧮 Bonus — Excel Prototype

Before writing a single line of C, I built a manual simulation in Excel to verify
the math step by step. It was made around the same time as the C project,
toward the end of development, as a cross-check tool.

> Files: `Classeur_reseau_de_neurone_v1.xlsx`

### Global view — one iteration block per row group

<div align="center">
  <img src="Images/Classeur_excel-Vu_globale.png" alt="Excel global view">
</div>

Each "block" of rows represents one training iteration. You can visually follow
how the weights drift across the entire training run just by scrolling down.

### Local view — anatomy of one iteration

<div align="center">
  <img src="Images/Classeur_excel-Vu_local.png" alt="Excel local view">
</div>

For the first layer :
| Zone | Location | Role |
|---|---|---|
| **Inputs** (`Valeur entrée`) | Column B / F / J / T / ... | Raw input fed into each neuron |
| **Weights** (`Weight`) | Column C / G / K / U / ... | Learnable parameters — updated each iteration |
| **Pre-activation** (`Output =/= sig`) | Column D / H / L / V / ... | Weighted sum before sigmoid |
| **Activation** (`Output sig`) | Column E / I / M / W / ... | Sigmoid output — becomes next layer's input |
| **Hyperparameters** (`Delta learning`) | Cell O7 | Learning rate α used in weight update |
| **Loss** (`Erreur moy`) | Cell O3 / O34 / ... | Mean error over the current iteration |
| **Target / Output / Error** | Small table in the middle | Ground truth vs prediction, per sample |
| **Backprop deltas** (`Calcul de delta`) | Bottom of each iteration block | Gradients propagated back through layers |

The 3 layer groups (`Couche 1`, `Couche 2`, `Couche 3`) are repeated left-to-right
for the two training samples, then mirrored on the right side for the weight-update pass.

> ⚠️ Not optimized — purely a pedagogical debugging artifact to validate the C math.

---

## 📖 Inspiration / Sources  
This project is based on a basic book named "L'intelligence artificielle pour les dévellopeurs" from Virginie MATHIVET.  
It just explain who work a neuron, that's all 🤯 !

---

# ✍️ P.S. 
I coded this in 2023-2024 so it is not so well optimized ! I was a beginner. 😆  
Code created by me 😎, Thibault GAREL - [Github](https://github.com/Thibault-GAREL)
