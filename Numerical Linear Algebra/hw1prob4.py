import numpy as np

def _to_index(x:float, x_axis:np.array) -> int:
    '''
    maps a coordinate x to the nearest valid index into an array sampled
    over x_axis, clamped to the array's bounds
    '''
    dx = x_axis[1] - x_axis[0]
    index = round((x - x_axis[0]) / dx)
    return min(max(index, 0), len(x_axis) - 1)

def bisection_method(f:np.array, x_axis:np.array, a:float, b:float, epsilon:float)-> float:
    '''
    f is a numpy array of samples of a continuous function over x_axis
    (i.e. f[_to_index(x, x_axis)] approximates f(x))
    we want to find a root in [a,b]
    we continue running until |x_k-x_{k-1}|<epsilon
    outputting an x value for a root of f in [a,b], along with the
    sequence of midpoints visited at each iteration
    '''
    if np.sign(f[_to_index(a, x_axis)]) == np.sign(f[_to_index(b, x_axis)]):
        raise ValueError("Signs must be opposite at ends of the interval to use bisection method")

    x_history = []
    x_prev = a
    while True:
        midpoint = (a + b) / 2
        x_history.append(midpoint)

        if f[_to_index(midpoint, x_axis)] == 0 or abs(midpoint - x_prev) < epsilon:
            return midpoint, x_history

        if np.sign(f[_to_index(midpoint, x_axis)]) == np.sign(f[_to_index(a, x_axis)]):
            a = midpoint
        else:
            b = midpoint
        x_prev = midpoint

def newton_method(f:np.array, f_prime:np.array, x_axis:np.array, x0:float, epsilon:float, tolerance: int)-> float:
    '''
    f and f_prime are numpy arrays of samples of a differentiable function
    and its derivative over x_axis (i.e. f[_to_index(x, x_axis)] approximates f(x))
    x0 is the initial guess
    we continue running until |x_k-x_{k-1}|<epsilon
    OR until we have run more than tolerance iterations
    outputting an x value for a root of f, along with the sequence of
    iterates x_k visited
    '''
    x_history = [x0]
    x_k = x0

    for _ in range(tolerance):
        f_val = f[_to_index(x_k, x_axis)]
        f_prime_val = f_prime[_to_index(x_k, x_axis)]
        if f_prime_val == 0:
            raise ZeroDivisionError("f_prime is zero at this iterate; Newton's method fails")

        x_next = x_k - f_val / f_prime_val
        x_history.append(x_next)

        if abs(x_next - x_k) < epsilon:
            return x_next, x_history

        x_k = x_next

    return x_k, x_history

#test on f(x) = x^3 - 2x^2 + 1 on [1,3]

x_axis = np.linspace(1,3,num=100)
f = x_axis**3-2*x_axis**2+1
f_prime = 3*x_axis**2-4*x_axis #computed by hand

newton_root, newton_his = newton_method(f, f_prime, x_axis, 2, 0.01, 50)
bisect_root, bisect_his = bisection_method(f, x_axis, 1, 3, 0.01)

print("Newton's Root: ",newton_root)
print("Newton's History: ",newton_his)
print("Bisection Root: ",bisect_root)
print("Bisection History: ",bisect_his)
