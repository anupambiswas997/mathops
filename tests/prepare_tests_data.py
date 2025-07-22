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

# vector -> [1.23, 4.56, -3.45] (can also be in numpy 1d array form)
def write_vector_data(vector_data, filepath):
    data = [size_t_elem(len(vector_data))] + [double_elem(e) for e in vector_data]
    write_binary_data(data, filepath)

# sparse_vector -> (10, # vector size
#                   3.2, # default value
#                   {1: -2.34, 4: 0.0032, 8: -8.54}) # content
def write_sparse_vector_data(sparse_vector_data, filepath):
    size, defval, content = sparse_vector_data
    data = [size_t_elem(size), double_elem(defval), size_t_elem(len(content.keys()))]
    for k,v in content.items():
        data.extend([size_t_elem(k), double_elem(v)])
    write_binary_data(data, filepath)

# matrix -> [[-3, 4.52], [-7.09, 12.32]] (can also be in numpy 2d array form)
def write_matrix_data(matrix_data, filepath):
    nrows, ncols = matrix_data.shape
    data = [size_t_elem(nrows), size_t_elem(ncols)]
    data.extend([double_elem(matrix_data[i][j]) for i in range(nrows) for j in range(ncols)])
    write_binary_data(data, filepath)

# sparse_matrix -> (2, # number of rows
#                   3, # number of columns
#                   8.43, # default value
#                   {0: {2: 3.01}, 1: {0: 1.2, 2: -0.9}}) # content
def write_sparse_matrix_data(sparse_matrix_data, filepath):
    nrows, ncols, defval, content = sparse_matrix_data
    data = [size_t_elem(nrows), size_t_elem(ncols), double_elem(defval)]
    content_part = []
    num_elems = 0
    for i,v in content.items():
        for j,value in v.items():
            content_part.extend([size_t_elem(i), size_t_elem(j), double_elem(value)])
            num_elems += 1
    data.append(size_t_elem(num_elems))
    data.extend(content_part)
    write_binary_data(data, filepath)

# dim -> (5,) for vector, (3, 4) for matrix
def get_random_matvec(start, end, dim):
    diff = end - start
    matvec = np.random.random(dim) * diff + start
    return matvec, matvec

def get_random_sparse_vec(start, end, size, num_elems):
    diff = end - start
    defval = np.random.random() * diff + start
    content = {}
    added = set()
    spvec_np = np.full((size,), defval)
    while len(added) < num_elems:
        i = random.randrange(size)
        content[i] = np.random.random() * diff + start
        spvec_np[i] = content[i]
        added.add(i)
    spvec = (size, defval, content,)
    return spvec, spvec_np

def get_random_sparse_mat(start, end, nrows, ncols, num_elems):
    diff = end - start
    defval = np.random.random() * diff + start
    content = {}
    added = set()
    spmat_np = np.full((nrows, ncols), defval)
    while len(added) < num_elems:
        i = random.randrange(nrows)
        j = random.randrange(ncols)
        ij = f"{i}_{j}"
        if not i in content.keys():
            content[i] = {}
        content[i][j] = np.random.random() * diff + start
        spmat_np[i][j] = content[i][j]
        added.add(ij)
    spmat = (nrows, ncols, defval, content,)
    return spmat, spmat_np

def indent(text, ind):
    return "\n".join([f"{ind}{l}" for l in text.split("\n")])

def pad(text, maxlen):
    tstr = str(text)
    return tstr + (((maxlen - len(tstr)) * ' ') if maxlen > len(tstr) else '')

def get_matrix_text(m, var_name):
    maxlen = max([len(str(m[i][j])) for i in range(m.shape[0]) for j in range(m.shape[1])])
    lines = [('{' + ', '.join([pad(e, maxlen) for e in m[i]]) + '}') for i in range(m.shape[0])]
    return f"Matrix {var_name}(" + "{\n    " + ",\n    ".join(lines) + "\n});"

def get_vector_text(v, var_name):
    maxlen = max([len(str(e)) for e in v])
    return f"Vector {var_name}(" + "{" + ', '.join([pad(e, maxlen) for e in v]) + "});"

def get_sparse_matrix_text(sm, var_name):
    nrows, ncols, defval, content = sm
    sm_text = f"SparseMatrix {var_name}({defval}, {nrows}, {ncols});"
    for i,v in content.items():
        for j,value in v.items():
            sm_text += f"\n{var_name}[{i}][{j}] = {value};"
    return sm_text

def get_sparse_vector_text(sv, var_name):
    size, defval, content = sv
    sv_text = f"SparseVector {var_name}({defval}, {size});"
    for i,value in content.items():
        sv_text += f"\n{var_name}[{i}] = {value};"
    return sv_text

# create_test('m', (5, 3), 'sm', (3, 4), '*')
def create_test(typ1, dim1, typ2, dim2, oper):
    pass

if __name__ == '__main__':
    #print(get_random_sparse_mat(-2, 2, 3, 4, 5))
    #print("\n".join([f"i={i},j={j}" for i in range(3) for j in range(6,9)]))
    print(get_matrix_text(get_random_matvec(0, 1, (3, 4))[0], "ma"))
    print(get_vector_text(get_random_matvec(-2, 2, (5,))[0], "vb"))
    print(get_sparse_matrix_text(get_random_sparse_mat(-3, 3, 4, 3, 5)[0], "smc"))
    print(get_sparse_vector_text(get_random_sparse_vec(-10, 10, 20, 7)[0], "svd"))