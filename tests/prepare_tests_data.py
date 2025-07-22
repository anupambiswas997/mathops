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

def get_random_spmatvec(start, end, dim):
    is_vector = len(dim) == 1
    # 40% filling for sparse vector/matrix
    num_elems = int(0.4 * dim[0]) if is_vector else int(0.4 * dim[0] * dim[1])
    return get_random_sparse_vec(start, end, dim[0], num_elems) if is_vector else get_random_sparse_mat(start, end, dim[0], dim[1], num_elems)

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
def varfunc(ty):
    return get_random_spmatvec if 's' in ty else get_random_matvec

def txtfunc(ty):
    return {
        'm': get_matrix_text,
        'v': get_vector_text,
        'sm': get_sparse_matrix_text,
        'sv': get_sparse_vector_text
    }[ty]

def get_test(typa, dima, typb, dimb, oper, test_name):
    a, a_np = varfunc(typa)(-5, 5, dima)
    b, b_np = varfunc(typb)(-5, 5, dimb)
    a_txt = txtfunc(typa)(a, 'a')
    b_txt = txtfunc(typb)(b, 'b')
    if oper in ['*', 'dot']:
        r_np = a_np.dot(b_np)
    elif oper == '+':
        r_np = a_np + b_np
    elif oper == '-':
        r_np = a_np - b_np
    if oper == 'dot':
        r_txt = f"double expected = {r_np};"
        op_txt = "a.dot(b)"
        check_txt = f"bool passed = ({op_txt} == expected);"
    else:
        if len(r_np.shape) == 2:
            r_txt = get_matrix_text(r_np, 'expected').replace('Matrix', 'vector<vector<double> >')
            dim_txt = f"{r_np.shape[0]}, {r_np.shape[1]}"
        else:
            r_txt = get_vector_text(r_np, 'expected').replace('Vector', 'vector<double>')
            dim_txt = f"{r_np.shape[0]}"
        op_txt = f"a {oper} b"
        check_txt = f"bool passed = areEqual({op_txt}, expected, {dim_txt}, 1.0e-8);"
    test_params_txt = f"testParamsList.push_back(TestParams(\"{test_name}\", passed));"
    msg_txt = f"cout << \"TEST: {test_name}\" << endl;"
    res_txt = f"cout << \"    passed: \" << passed << endl;"
    test_code = "{\n" + indent("\n".join([msg_txt, a_txt, b_txt, r_txt, check_txt, test_params_txt, res_txt]), "    ") + "\n}"
    #print(test_code)
    return test_code

def get_test_suite():
    opers = {
        '*': [
            ['m', 'm'], ['m', 'sm'], ['m', 'v'], ['m', 'sv'],
            ['sm', 'm'], ['sm', 'sm'], ['sm', 'v'], ['sm', 'sv'],
            ['v', 'm'], ['v', 'sm'],
            ['sv', 'm'], ['sv', 'sm']
        ],
        'dot': [
            ['v', 'v'], ['v', 'sv'],
            ['sv', 'v'], ['sv', 'v']
        ],
        '+': [
            ['m', 'm'], ['m', 'sm'],
            ['sm', 'm'], ['sm', 'sm'],
            ['v', 'v'], ['v', 'sv'],
            ['sv', 'v'], ['sv', 'sv']
        ],
        '-': [
            ['m', 'm'], ['m', 'sm'],
            ['sm', 'm'], ['sm', 'sm'],
            ['v', 'v'], ['v', 'sv'],
            ['sv', 'v'], ['sv', 'sv']
        ]
    }
    test_codes = []
    full_names = {'m': 'Matrix', 'v': 'Vector', 'sm': 'SparseMatrix', 'sv': 'SparseVector'}
    for op,oplist in opers.items():
        for typa, typb in oplist:
            test_name = f"{full_names[typa]} {op} {full_names[typb]}"
            n1 = random.randrange(5, 10)
            n2 = random.randrange(5, 10)
            n3 = random.randrange(5, 10)
            if op in ['+', '-']:
                dima = (n1, n2) if 'm' in typa else (n1,)
                dimb = dima
            elif op == '*':
                dima = (n1, n2) if 'm' in typa else (n2,)
                dimb = (n2, n3) if 'm' in typb else (n2,)
            elif op == 'dot':
                dima = (n1,)
                dimb = dima
            test_code = get_test(typa, dima, typb, dimb, op, test_name)
            print(test_code)
            test_codes.append(test_code)
    with open("tests/t.cpp", "w") as f:
        f.write("""
#include "test_base.hpp"
#include <vector>

using namespace std;

vector<TestParams> performLinearAlgebraTests()
{
    vector<TestParams> testParamsList = {};

""" + indent("\n".join(test_codes), "    ") + """ 
    return testParamsList;
}

int main(int argc, char *argv[])
{
    vector<TestParams> testResults = performLinearAlgebraTests();
    for(const auto& tParam: testResults)
    {
        cout << tParam.name << ": " << (tParam.passed ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
""")

if __name__ == '__main__':
    #print(get_random_sparse_mat(-2, 2, 3, 4, 5))
    #print("\n".join([f"i={i},j={j}" for i in range(3) for j in range(6,9)]))
    #print(get_matrix_text(get_random_matvec(0, 1, (3, 4))[0], "ma"))
    #print(get_vector_text(get_random_matvec(-2, 2, (5,))[0], "vb"))
    #print(get_sparse_matrix_text(get_random_sparse_mat(-3, 3, 4, 3, 5)[0], "smc"))
    #print(get_sparse_vector_text(get_random_sparse_vec(-10, 10, 20, 7)[0], "svd"))
    #print(get_sparse_matrix_text(get_random_spmatvec(15, 20, (2, 3))[0], "sme"))
    #print(get_sparse_vector_text(get_random_spmatvec(0, 4, (3,))[0], "svf"))
    #get_test('m', (5, 3), 'sm', (3, 4), '*', "Matrix * SparseMatrix")
    get_test_suite()