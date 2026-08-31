
                                                                                                                                                                                                 

import numpy as np
 
def vandermonde(n, m):
    i = np.arange(1, n+1)
    x = (i - 1) / (m - 1)
    A = np.vander(x, N=m, increasing=True)
    return A
 
def classical_gs(A):
    n, m = A.shape
    Q = np.zeros((n, m))
    R = np.zeros((m, m))
    for j in range(m):
        v = A[:, j].copy()
        for i in range(j):
            R[i, j] = Q[:, i] @ A[:, j]
            v = v - R[i, j] * Q[:, i]
        R[j, j] = np.linalg.norm(v)
        Q[:, j] = v / R[j, j]
    return Q, R
 
def modified_gs(A):
    n, m = A.shape
    V = A.copy()
    Q = np.zeros((n, m))
    R = np.zeros((m, m))
    for i in range(m):
        R[i, i] = np.linalg.norm(V[:, i])
        Q[:, i] = V[:, i] / R[i, i]
        for j in range(i+1, m):
            R[i, j] = Q[:, i] @ V[:, j]
            V[:, j] = V[:, j] - R[i, j] * Q[:, i]
    return Q, R
 
def double_gs(A):
    # Apply classical Gram-Schmidt twice (reorthogonalization)
    Q1, R1 = classical_gs(A)
    Q2, R2 = classical_gs(Q1)
    Q = Q2
    R = R2 @ R1
    return Q, R
 
def householder_qr(A):
    Q, R = np.linalg.qr(A, mode='reduced')
    return Q, R
 
def ortho_error(Q):
    m = Q.shape[1]
    G = Q.T @ Q
    off = G - np.diag(np.diag(G))
    return np.max(np.abs(off))
 
n = 80
ms = [4, 6, 8, 12, 14]
 
results = {}
for m in ms:
    A = vandermonde(n, m)
    Qcgs, _ = classical_gs(A)
    Qmgs, _ = modified_gs(A)
    Qdgs, _ = double_gs(A)
    Qhh, _ = householder_qr(A)
 
    Ecgs = ortho_error(Qcgs)
    Emgs = ortho_error(Qmgs)
    Edgs = ortho_error(Qdgs)
    Ehh = ortho_error(Qhh)
 
    results[m] = (Ecgs, Emgs, Edgs, Ehh)
 
print(f"{'m':>4} | {'CGS':>12} | {'MGS':>12} | {'Double GS':>12} | {'Householder':>12}")
print("-"*65)
for m in ms:
    Ecgs, Emgs, Edgs, Ehh = results[m]
    print(f"{m:>4} | {Ecgs:12.3e} | {Emgs:12.3e} | {Edgs:12.3e} | {Ehh:12.3e}")
 
