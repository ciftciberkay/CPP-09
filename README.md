*This project has been created as part of the 42 curriculum by beciftci.*

# CPP-09 · Containers and algorithms

Three CLI programs that apply standard containers to real inputs. Each exercise has its own Makefile.

## Exercises

| Directory | Exercise | Focus |
| --- | --- | --- |
| [ex00](./ex00) | BitcoinExchange | Look up historical exchange rates by date. |
| [ex01](./ex01) | RPN | Evaluate reverse Polish notation with a stack. |
| [ex02](./ex02) | PmergeMe | Compare merge-insertion sorting with two container types. |

## Build and run

Run these commands from the repository root with a C++98 compatible compiler and Make.

```sh
make -C ex01
./ex01/RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

To build another exercise, pass its directory to `make -C`.

To run BitcoinExchange, place the historical rate file `data.csv` in `ex00/`. Run `./btc <input-file>` from that directory. The rate database is supplied separately.
