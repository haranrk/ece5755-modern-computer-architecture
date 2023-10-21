import timeit
import fire
import matplotlib.pyplot as plt
import subprocess

PLOTS_DIR = "plots"


def benchmark(f, args, iterations=1):
    runtimes = timeit.repeat(lambda: f(*args), number=1, repeat=iterations)
    return sorted(runtimes)[iterations // 2]


def run_shell_cmd(cmd):
    print(cmd)
    subprocess.run(cmd, shell=True)


def compare_diff_block_sizes():
    runtimes = []
    block_sizes = [1, 2, 4, 8, 64, 70, 80, 90, 100, 128, 256, 512]
    # block_sizes = [60, 80, 100, 120, 140, 160, 180, 200,220, 240, 260]
    dims = 1024
    iterations = 2
    shell_cmd_prefix = ["./main.out", "SPARSE", str(dims)]
    shell_cmd_postfix = [str(iterations)]

    for block_size in block_sizes:
        cmd = " ".join(shell_cmd_prefix + [str(block_size)] + shell_cmd_postfix)
        runtimes.append(benchmark(run_shell_cmd, [cmd]))
    print(runtimes)
    plt.plot(block_sizes, runtimes, label="Block size comparison", marker="o")
    plt.xlabel("Block Size")
    plt.ylabel("Runtime (s)")
    plt.title("Performance Analysis")
    plt.grid(True)
    plt.savefig(
        f"{PLOTS_DIR}/block_size_comparison_{min(block_sizes)}to{max(block_sizes)}.png"
    )
    plt.show()
    plt.clf()


def compare_diff_block_sizes_with_naive_baseline():
    runtimes_naive = []
    runtimes_tiled = []
    dims = 1024
    block_sizes = [1, 2, 4, 8, 64, 70, 80, 90, 100, 128, 256, 512, 1024]
    iterations = 3
    for block_sz in block_sizes:
        cmd = " ".join(
            ["./main.out", "NAIVE", str(dims), str(block_sz), str(iterations)]
        )
        runtimes_naive.append(benchmark(run_shell_cmd, [cmd]))
        cmd = " ".join(
            ["./main.out", "SPARSE", str(dims), str(block_sz), str(iterations)]
        )
        runtimes_tiled.append(benchmark(run_shell_cmd, [cmd]))

    print(runtimes_naive, runtimes_tiled)
    plt.plot(block_sizes, runtimes_naive, label="Naive", marker="o")
    plt.plot(block_sizes, runtimes_tiled, label="SPARSE", marker="o")
    plt.xlabel("Block Size")
    plt.ylabel("Runtime (s)")
    plt.title(f"Naive vs SPARSE Performance Analysis (dims={dims})")
    plt.legend()
    plt.grid(True)
    plt.savefig(
        f"{PLOTS_DIR}/block_size_comparison_naive_vs_tiled_{dims=}_{min(block_sizes)}to{max(block_sizes)}.png"
    )
    plt.show()
    plt.clf()


def compare_naive_vs_tiled(block_size=128):
    runtimes_naive = []
    runtimes_tiled = []
    dims = [3, 10, 128, 512 ]
    shell_cmd_prefix = ["./main.out"]

    for dim in dims:
        cmd = " ".join(shell_cmd_prefix + ["NAIVE", str(dim), "1", "10"])
        runtimes_naive.append(benchmark(run_shell_cmd, [cmd]))
        cmd = " ".join(shell_cmd_prefix + ["SPARSE", str(dim), "1", "1"])
        runtimes_tiled.append(benchmark(run_shell_cmd, [cmd]))

    plt.plot(dims, runtimes_naive, label="Naive", marker="o")
    plt.plot(dims, runtimes_tiled, label="SPARSE", marker="o")
    plt.xlabel("Matrix Dimension")
    plt.ylabel("Runtime (s)")
    plt.title(f"Naive vs Sparse Performance Analysis")
    plt.legend()
    plt.grid(True)
    plt.savefig(f"{PLOTS_DIR}/naive_vs_tiled_2.png")
    plt.show()
    plt.clf()


def plot_top_down():
    categories = ["Frontend Bound", "Bad Speculation", "Backend Bound", "Retiring"]

    # Data for "256x256" (updated)
    # slots_128x128 = [9.7, 1.3, 1.6, 87.4]
    slots_128x128 = [3.4, 0.2, 28.5, 67.8]

    # Data for "512x512" (updated)
    # slots_256x256 = [9.2, 1.0, 0.6, 89.2]
    slots_256x256 = [32.4, 2.7, 18.7, 46.2]

    # Data for "1024x1024" (updated)
    # slots_1024x1024 = [8.9, 1.0, 0.9, 89.2]
    # slots_1024x1024 = [14.3, 0.3, 2.3, 83.1]
    
    percent_slots = [
        slots_256x256,
        slots_128x128,
    ]

    bubbles = ["Matmul", "Sparse Matmul" ]

    colors = ["#419D78", "#3C91E6", "#904E55", "#6C596E"]
    _,ax = plt.subplots()

    for i, bubble in enumerate(bubbles):
        left = 0
        for j, category in enumerate(categories):
            width = percent_slots[i][j]
            ax.barh(bubble, width, left=left, color=colors[j], label=category)
            left += width

    ax.set_xlabel("%")
    block_size = 1
    suffix = f"{block_size=}"
    ax.set_title(f"Pipeline Bottleneck Breakdown")
    ax.legend(categories, loc="upper right")

    print(f"{PLOTS_DIR}/pipeline_bottleneck_breakdown{suffix}.png")
    plt.savefig(f"{PLOTS_DIR}/pipeline_bottleneck_breakdown{suffix}.png")
    plt.show()


if __name__ == "__main__":
    # compare_diff_block_sizes()
    # compare_diff_block_sizes_with_naive_baseline()

    # block_sizes = [1,80, 128]
    # block_sizes.extend([256, 512, 1024])
    # block_sizes.extend([140, 160, 180, 200,220, 240, 260])
    # for block_sz in block_sizes:
    # compare_naive_vs_tiled(1)
    plot_top_down()
    # fire.Fire()
    print("Finished")
