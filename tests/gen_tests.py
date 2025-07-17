import numpy as np
import random

def get_matrix_text(mat, var_name):
    mat_cpp_text = f"Matrix {var_name}(" + "{\n    "
    mat_cpp_text += ",\n    ".join([("{" + ", ".join([str(e) for e in mat[i]]) + "}") for i in range(mat.shape[0])]) + "\n"
    mat_cpp_text += "});"
    return mat_cpp_text

def get_matrix_and_text(nrows, ncols, start, end, var_name):
    mat = np.random.random((nrows, ncols)) * (end - start) + start
    return mat, get_matrix_text(mat, var_name)

a, b = get_matrix_and_text(2, 3, 0, 5, 'm')
print(a)
print(b)