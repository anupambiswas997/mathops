"""
PURPOSE OF SCRIPT:
This script is used to auto-generate linear algebra tests, in the file
'linear_algebra_tests.hpp'. In linear algebra, there are multiplication,
addition and subtraction operations between objects of the following kind:
  - Matrix
  - SparseMatrix
  - Vector
  - SparseVector
Also, each of the above classes also have similar operations with constants.
Plus, there are matrix inversion tests for two matrix classes. In total,
there are about 46 tests, and hand-writing them is time-consuming, and also
prone to error. So, this script facilitates that task and uses Python's
numpy library to generated the expected answers for the matrix and vector
operations.

USAGE:
From repository root, issue the following command:

  > python tests/prepare_tests_data.py

This, however will overwrite the version-controlled file 'linear_algebra_tests.hpp'.
So, if the newly generated version of the file is needed, it must be staged and
committed again.
"""

import random
import numpy as np

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
        check_txt = f"passed = ({op_txt} == expected);"
    else:
        if len(r_np.shape) == 2:
            r_txt = get_matrix_text(r_np, 'expected').replace('Matrix', 'vector<vector<double> >')
            dim_txt = f"{r_np.shape[0]}, {r_np.shape[1]}"
        else:
            r_txt = get_vector_text(r_np, 'expected').replace('Vector', 'vector<double>')
            dim_txt = f"{r_np.shape[0]}"
        op_txt = f"a {oper} b"
        check_txt = f"passed = areEqual({op_txt}, expected, {dim_txt}, 1.0e-8);"
    test_params_txt = f"testParamsList.push_back(TestParams(testName, passed));"
    msg_txt = f"testName = \"{test_name}\";\ncout << \"TEST: \" << testName << endl;"
    res_txt = f"cout << \"    passed: \" << passed << endl;"
    test_code = "{\n" + indent("\n".join([msg_txt, a_txt, b_txt, r_txt, check_txt, test_params_txt, res_txt]), "    ") + "\n}"
    #print(test_code)
    return test_code

def get_const_test(typ, dim, oper, test_name):
    msg_txt = f"testName = \"{test_name}\";\ncout << \"TEST: \" << testName << endl;"
    a, a_np = varfunc(typ)(-5, 5, dim)
    a_txt = txtfunc(typ)(a, 'a')
    c = np.random.random() * 10 - 5 # between -5 and 5
    c_txt = f"double c = {c};"
    if oper == '+':
        r_np = a_np + c
    elif oper == '-':
        r_np = a_np - c
    elif oper == '*':
        r_np = a_np * c
    if len(dim) == 1:
        r_txt = get_vector_text(r_np, 'expected').replace('Vector', 'vector<double>')
    elif len(dim) == 2:
        r_txt = get_matrix_text(r_np, 'expected').replace('Matrix', 'vector<vector<double> >')
    op_txt = f"a {oper} c"
    dim_txt = f"{dim[0]}" if len(dim) == 1 else f"{dim[0]}, {dim[1]}"
    check_txt = f"passed = areEqual({op_txt}, expected, {dim_txt}, 1.0e-8);"
    test_params_txt = "testParamsList.push_back(TestParams(testName, passed));"
    test_code = "{\n" + indent("\n".join([msg_txt, a_txt, c_txt, r_txt, check_txt, test_params_txt]), "    ") + "\n}"
    return test_code

def get_inverse_tests():
    # matrix inverse test code
    msg_txt = f"testName = \"Matrix inverse\";cout << \"TEST: \" << testName << endl;"
    n = random.randrange(5, 8)
    a, a_np = get_random_matvec(-5, 5, (n, n))
    a_txt = get_matrix_text(a, 'a')
    ainv_np = np.linalg.inv(a_np)
    r_txt = get_matrix_text(ainv_np, 'expected').replace('Matrix', 'vector<vector<double> >')
    check_txt = f"passed = areEqual(a.getInverse(), expected, {n}, {n}, 1.0e-8);"
    test_params_txt = "testParamsList.push_back(TestParams(testName, passed));"
    test_code_mat = "{\n" + indent("\n".join([msg_txt, a_txt, r_txt, check_txt, test_params_txt]), "    ") + "\n}"

    # sparse matrix inverse test code
    msg_txt = f"testName = \"SparseMatrix inverse\";cout << \"TEST: \" << testName << endl;"
    n = random.randrange(5, 8)
    a, a_np = get_random_spmatvec(-5, 5, (n, n))
    a_txt = get_sparse_matrix_text(a, 'a')
    ainv_np = np.linalg.inv(a_np)
    r_txt = get_matrix_text(ainv_np, 'expected').replace('Matrix', 'vector<vector<double> >')
    check_txt = f"passed = areEqual(a.getFullMatrix().getInverse(), expected, {n}, {n}, 1.0e-8);"
    test_params_txt = "testParamsList.push_back(TestParams(testName, passed));"
    test_code_spmat = "{\n" + indent("\n".join([msg_txt, a_txt, r_txt, check_txt, test_params_txt]), "    ") + "\n}"

    return [test_code_mat, test_code_spmat]

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
            ['sv', 'v'], ['sv', 'sv']
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
    for op in ['+', '-', '*']:
        for ty in ['m', 'sm', 'v', 'sv']:
            test_name = f"{full_names[ty]} {op} constant"
            n1 = random.randrange(5, 8)
            n2 = random.randrange(5, 8)
            dim = (n1, n2) if 'm' in ty else (n1,)
            test_codes.append(get_const_test(ty, dim, op, test_name))
    test_codes.extend(get_inverse_tests())
    with open("tests/linear_algebra_tests.hpp", "w") as f:
        f.write("""
#include "test_base.hpp"
#include <vector>

using namespace std;

void performLinearAlgebraTests(vector<TestParams>& testParamsList)
{
    string testName;
    bool passed;
""" + indent("\n".join(test_codes), "    ") + """
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