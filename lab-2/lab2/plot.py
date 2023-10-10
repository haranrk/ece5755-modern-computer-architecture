import timeit
import subprocess


def benchmark(f, args, iterations=20):
    runtimes = timeit.repeat(lambda: f(*args), number=1, repeat=iterations)
    return sorted(runtimes)[iterations // 2]
  
def run_c():
  res = subprocess.run(["make", "test"], shell=True)
  print(res)
  
if __name__ == "__main__":
  print(benchmark(run_c,[], iterations=5))



