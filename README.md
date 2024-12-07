<h1 align="center">
  <img src="assets/philosophers.png" alt="philosophers" width="400">
</h1>

<p align="center">
    <b><i>Solving concurrency synchronization issues in multithreading 🧵.</i></b><br>
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

Goal of the project is to explore [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in multithreaded environment.

For each philosophers, there is `equal` amount of `forks` and they need `two` forks to begin the meal.

Eating takes a set duration in `milliseconds`. Then they `sleep` and finally commence `thinking` again.

Philosopher will die if it can't `begin` a meal within time to die since `taking forks`.

Dining will `end` if any of the philosophers is `death` or everyone has `eaten` the set amount of `meals`.

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

If `meals count` is not provided and `time to die` is long enough, the simulation will run infinitely.

```bash
./philo 2 610 300 200 3
```

```bash
./philo 2 610 300 200
```

Every `event` is printed to `STDOUT`. Here is an example where philosopher dies. 

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

```bash
./philo 2 500 300 200 abc
```

```bash
Error: abc: Is invalid argument
```

## 🚀 Details

After initialization the `process manager` is responsible for managing `threads` and `mutexes`.

To help this and overall process, `operater` functions are used as wrappers.

```c
operate_thread(&data->monitor, OP_DETACH, data, NULL);
```

```c
operate_mutex(&data->mutex[i++], OP_INIT, data);
```

Lastly the `monitor` thread is created to overview the dining `routine`.

```c
void *process_monitor(void *param)
{
  t_data	*data;

  data = (t_data *)param;
  threads_spinlocked(data);
  while (true)
  {
    if (process_finished(data)
      || process_failed(data))
      break ;
    else if (philosopher_death(data)
      || philosophers_full(data))
      set_finished(data);
  }
  return (NULL);
}
```

Since `usleep` is not natively precise enough, custom `precision_sleep` is used instead.

```c
void percision_sleep(long target, t_data *data)
{
  long	start;

  target = convert_to_micro_second(target);
  start = operate_timer(OP_USEC, data);
  while (gettime(start, data) < target)
  {
    if (process_finished(data) || process_failed(data))
      break ;
    usleep(500);
  }
}
```

Main `data` and `each` philosopher have `enumerated` boolean statuses and their corresponding mutexes.

```c
typedef struct s_data
{
  [...]
  t_mtx   mutex[MTX_COUNT_DATA];
  bool    stat[STT_COUNT_DATA];
} t_data;
```

These are used by `getset` functions and `synchro` utilities to view and change process states.

```c
void threads_synchronized(t_data *data)
{
  set_status(&data->stat[ST_SYNC], true, &data->mutex[MX_SYNC], data);
}
```

```c
void threads_spinlocked(t_data *data)
{
  while (!get_status(&data->stat[ST_SYNC], &data->mutex[MX_SYNC], data))
    true ;
}
```

## ♻️ Resources

[Unix Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) video playlist on multithreading in C.

[The dining Philosophers in C](https://www.youtube.com/watch?v=zOpzGHwJ3MU) detailed video explanation of dining philosophers.

[Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer-v2/) fantastic tool to visualize your philosophers.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42](https://github.com/Jarnomer/Hive42) page.

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳