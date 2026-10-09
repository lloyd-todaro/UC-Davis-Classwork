# Homework 2, Problem 1
# Regula Falsi
import numpy as np

def regula_falsi(f:np.array, a:float, b:float, tol=1e-5, max_iter=100):
    """
    Regula Falsi method for finding roots of a function.

    Parameters:
    f : function
        The function for which we want to find the root.
    a : float
        The left endpoint of the interval.
    b : float
        The right endpoint of the interval.
    tol : float, optional
        The tolerance for convergence (default is 1e-5).
    max_iter : int, optional
        The maximum number of iterations (default is 100).

    Returns:
    c : float
        The approximate root of the function.
        
    Constraints:
    - The function f must have different signs at the endpoints a and b (i.e., f(a) * f(b) < 0).
    """
    
    if f(a) * f(b) >= 0:
        raise ValueError("The function must have different signs at the endpoints a and b.")
    
    for i in range(max_iter):
        # Calculate the point c using the Regula Falsi formula
        c = (f(b) * a -  f(a) * b) / (f(b) - f(a))
        
        # Check if the root is found or if we are within the tolerance
        if abs(f(c)) < tol or abs(b - a) < tol:
            return c, max_iter - i  # Return the root and the number of iterations left
        
        # Update the interval [a, b]
    
        if f(c) * f(a) < 0:
            b = c
        else:
            a = c
            
    raise ValueError("Maximum number of iterations reached without convergence.")

def secant_method(f:np.array, x0:float, x1:float, tol=1e-5, max_iter=100):
    """
    Secant method for finding roots of a function.

    Parameters:
    f : function
        The function for which we want to find the root.
    x0 : float
        The first initial guess.
    x1 : float
        The second initial guess.
    tol : float, optional
        The tolerance for convergence (default is 1e-5).
    max_iter : int, optional
        The maximum number of iterations (default is 100).

    Returns:
    c : float
        The approximate root of the function.
    """
    for i in range(max_iter):
        # Calculate the next approximation using the Secant formula
        c = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        
        # Check if the root is found or if we are within the tolerance
        if abs(f(c)) < tol or abs(c - x1) < tol:
            return c, max_iter - i  # Return the root and the number of iterations left
        
        # Update the guesses
        x0, x1 = x1, c
            
    raise ValueError("Maximum number of iterations reached without convergence.")


f = lambda x: x**3 - 2*x - 5
root = regula_falsi(f, 1, 3)
root2 = secant_method(f, 1, 1.1)
print(f"The root found is: {root[0]}, in {root[1]} iterations.")
print(f"The root found is: {root2[0]}, in {root2[1]} iterations.")


def backwards_substitution(R, b):
    n = len(b)
    x = np.zeros(n)

    for i in range(n - 1, -1, -1):
        total = 0.0

        for j in range(i + 1, n):
            total += R[i, j] * x[j]

        x[i] = (b[i] - total) / R[i, i]

    return x

import time

start = time.perf_counter()

x = backwards_substitution(R, b)

end = time.perf_counter()

runtime = end - start



