import sys
import re
import os
import numpy as np

OB, CB = "{", "}"
OBCB = "{}"

def create_matrix_transpose_test(numrows, numcolumns):
    m = np.random.random((numrows, numcolumns))
    mT = m.T
    text = "Matrix mat = {};\n"
    for i in range(numrows):
        text += "mat.push_back({});\n"
        for j in range(numcolumns):
            text += f"mat[{i}].push_back({m[i][j]});\n"
    text += "Matrix matTransposed = getTranspose(mat);\n"
    text += "bool matT"
    text += "EXPECT()"
    print(m)
    print(m.T)
    print(text)

create_matrix_transpose_test(2, 3)