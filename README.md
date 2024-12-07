<h1 align="center">
  <img src="assets/philosophers.png" alt="philosophers" width="400">
</h1>

<p align="center">
    <b><i>Solving dining philosophers with multithreading 🧵.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-100%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/philosophers?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
    <img src="https://img.shields.io/github/languages/code-size/Jarnomer/philosophers?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/philosophers/sources?style=for-the-badge&label=sources&color=pink" alt="GitHub repo file or directory count (in path)">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/philosophers/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>

<div align="center">

## Table of Contents
[📝 General](#-general)
[🛠️ Build](#️-build)
[⚡ Usage](#-usage)
[🚀 Details](#-details)
[♻️ Resources](#️-resources)

</div>

## 📝 General

Goal of the project.

## 🛠️ Build

GNU `make` and `gcc` are required to build and compile the project.

```bash
git clone https://github.com/Jarnomer/philosophers.git
```

```bash
cd philosophers && make all
```

## ⚡ Usage

`Philosophers` are expecting these values and last one is optional.

| Value | Description            |
|-------|------------------------|
| 2     | Number of philosophers |
| 600   | Time to die (ms)       |
| 300   | Time to eat (ms)       |
| 200   | Time to sleep (ms)     |
| 4     | Number of meals (optional)       |

If `meals count` is not provided and `time to die` is long enough, simulation will run forever.

```bash
./philo 2 610 300 200 3
```

```bash
./philo 2 610 300 200
```

Philosopher will die if it can't `finish a meal` within time to die and `ends` the process.

```bash
./philo 2 500 300 200
```

```bash
0 2 is thinking
0 1 has taken fork
0 1 has taken fork
0 1 is eating
301 1 is sleeping
301 2 has taken fork
301 2 has taken fork
301 2 is eating
501 1 died
```

Incorrect input results to `Error`.

## 🚀 Details

[RESERVED]

## ♻️ Resources

[Unix Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) video playlist on multithreading in C.

[The dining Philosophers in C](https://www.youtube.com/watch?v=zOpzGHwJ3MU) detailed video explanation of dining philosophers.

[Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer-v2/) fantastic tool to visualize your philosophers.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42](https://github.com/Jarnomer/Hive42) page.

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳