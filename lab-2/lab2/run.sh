 python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./main.out TILED 128  1 10
 python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./main.out TILED 256  1 10
 python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./main.out TILED 1024 1 5