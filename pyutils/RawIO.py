import struct
import numpy as np


def dump(data, datapath):
    cols = 0x1 if len(data.shape) == 0x1 else data.shape[0x1]
    rows = data.shape[0x0]

    with open(datapath, "wb") as fd:
        fd.write(struct.pack("<i", cols))
        fd.write(struct.pack("<i", rows))
        for element in data.flatten():
            fd.write(element)


def load(datapath, dtype):
    with open(datapath, "rb") as fd:
        cols = np.frombuffer(fd.read(0x4), dtype=np.int32)[0x0]
        rows = np.frombuffer(fd.read(0x4), dtype=np.int32)[0x0]

        data = np.zeros((rows, cols), dtype=dtype)

        size = 0x4 if dtype == np.float32 else 0x8
        for i in range(rows):
            data[i] = np.frombuffer(fd.read(size * cols), dtype=dtype, count=cols)
        return data