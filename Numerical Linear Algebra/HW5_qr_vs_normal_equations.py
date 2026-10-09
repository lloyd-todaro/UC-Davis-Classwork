import numpy as np

def run_experiment(m, n=80):
    i = np.arange(1, n+1)
    x = (i - 1) / (n - 1)
    A = np.vander(x, N=m, increasing=True)
    a_true = np.ones(m)
    y = A @ a_true

    Q, R = np.linalg.qr(A, mode='reduced')
    a0 = np.linalg.solve(R, Q.T @ y)

    AtA = A.T @ A
    Aty = A.T @ y
    a1 = np.linalg.solve(AtA, Aty)

    rel_err_0 = np.linalg.norm(a_true - a0) / np.linalg.norm(a_true)
    rel_err_1 = np.linalg.norm(a_true - a1) / np.linalg.norm(a_true)

    cond_A = np.linalg.cond(A)
    cond_AtA = np.linalg.cond(AtA)

    return a0, a1, rel_err_0, rel_err_1, cond_A, cond_AtA

for m in [6, 12]:
    a0, a1, e0, e1, condA, condAtA = run_experiment(m)
    print(f"m = {m}")
    print(f"  rel error, QR method (a0)      = {e0:.4e}")
    print(f"  rel error, normal eqns (a1)    = {e1:.4e}")
    print(f"  cond(A)                        = {condA:.4e}")
    print(f"  cond(A^T A)                    = {condAtA:.4e}")
    print(f"  cond(A)^2  (should match above)= {condA**2:.4e}")
    print()
