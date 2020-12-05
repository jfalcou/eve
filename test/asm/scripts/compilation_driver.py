#!/usr/bin/env python3.9
from multiprocessing import Pool
import itertools

from generate_build_tasks import generate_build_tasks


def _rearrange_parts(parts):
    res = {}
    for arch, func_to_asm in parts:
        for func, asm in func_to_asm.items():
            key = f'{func}_{arch}.s'
            if not key in res:
                res[key] = ''
            res[key] += asm
    return res


def _split(a, n):
    k, m = divmod(len(a), n)
    return (a[i * k + min(i, m):(i + 1) * k + min(i + 1, m)] for i in range(n))


def _run_job(tasks):
    return [builder(sources) for builder, sources in tasks]


def compilation_arguments(parser):
    parser.add_argument('-j', '--jobs', type=int, required=False, default=4)
    parser.add_argument('--arches', type=str, nargs='+',
                        required=False, default=None)
    parser.add_argument('--sources', type=str, nargs='+',
                        required=False, default=None)
    parser.add_argument('--unity_block_size', type=int,
                        required=False, default=40)


def run_compilation(options):
    tasks = list(generate_build_tasks(options.arches,
                                      options.sources,
                                      options.unity_block_size))

    jobs = list(_split(tasks, options.jobs))

    parts = []
    with Pool(8) as pool:
        parts = pool.map(_run_job, jobs)

    return _rearrange_parts(itertools.chain(*parts))
