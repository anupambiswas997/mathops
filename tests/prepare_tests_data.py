from struct import pack
import random
import numpy as np

def write_binary_data(data, filepath):
    with open(filepath, 'wb') as f:
        for e in data:
            # data_type = N for size_t, d for double
            data_type, data_value = e
            f.write(pack(data_type, data_value))

def size_t_elem(x):
    return ['N', x]

def double_elem(x):
    return ['d', x]

def write_vector_data(vector_data, filepath):
    data = [size_t_elem(len(vector_data))] + [double_elem(e) for e in vector_data]
    write_binary_data(data, filepath)

# sparse_vector_data = {'size': 5, 'defval': 0.32, 'content': {1: 3.45, 4: -2.38}}
def write_sparse_vector_data(sparse_vector_data, filepath):
    size = sparse_vector_data['size']
    defval = sparse_vector_data['defval']
    content = sparse_vector['content']
    data = [size_t_elem(size), double_elem(defval)]
    for e in content:
        data.extend([size_t_elem(e[0]), double_elem(e[1])])
    write_binary_data(data, filepath)