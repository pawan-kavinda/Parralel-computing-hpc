# 🧮 Parallel Computing Project – Trapezoidal Integration

This project demonstrates numerical integration using the **Trapezoidal Rule**, implemented in **C** with four computation modes:

- ✅ **Serial Implementation**
- 🚀 **OpenMP (Shared Memory Parallelism)**
- 🌐 **MPI (Distributed Memory Parallelism)**
- 🧵🌐 **Hybrid (MPI + OpenMP)**

The goal is to compare the performance, speedup, and scalability of each method using the same mathematical function.

---

## 📌 Objective

To implement and evaluate the **Trapezoidal Rule** for approximating definite integrals using different parallel computing paradigms, measuring execution time and analyzing speedup and efficiency.

---

## 🔧 Technologies Used

- **C Programming Language**
- **MPI (Message Passing Interface)** – via `mpicc` and `mpirun`
- **OpenMP (Open Multi-Processing)** – via `gcc -fopenmp`
- **Hybrid** – combining MPI and OpenMP
- **Linux / WSL / Unix-based OS** for compilation and execution
- **Makefile** for simplified build

---

## 🧠 Methodology

We approximate the definite integral of a function `f(x)` over an interval `[a, b]` using:

`h = (b - a) / n` and `x_i = a + i * h`.

---

## 🧪 Implemented Versions

| Version      | Description                                       |
|--------------|---------------------------------------------------|
| `serial.c`   | Standard sequential implementation                |
| `openmp.c`   | Parallel implementation using OpenMP              |
| `mpi.c`      | Parallel implementation using MPI                 |
| `hybrid.c`   | Combined MPI + OpenMP for cluster + core-level parallelism |

---

## ⚙️ Compilation & Execution

### 🔧 Compile

# Serial
gcc serial.c -o serial

# OpenMP
gcc -fopenmp openmp.c -o openmp

# MPI
mpicc mpi.c -o mpi

# Hybrid (MPI + OpenMP)
mpicc -fopenmp hybrid.c -o hybrid

# 🚀 Run
## Serial
./serial

## OpenMP (8 threads)
export OMP_NUM_THREADS=8
./openmp

## MPI (4 processes)
mpirun -np 4 ./mpi

## Hybrid (4 MPI ranks x 2 threads each)
export OMP_NUM_THREADS=2
mpirun -np 4 ./hybrid

