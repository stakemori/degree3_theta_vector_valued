from sage.all import PolynomialRing, QQ, matrix, cached_function, ZZ, mul
from itertools import combinations, groupby


def poly_repn_dim(wt):
    return sum(schur_polynomial(wt).coefficients())


def schur_polynomial(wt):
    return _schur_polynomial_cached(tuple(wt))


@cached_function
def _schur_polynomial_cached(wt):
    n = len(wt)
    R = PolynomialRing(QQ, names=["x%s" % i for i in xrange(n)])
    l = [i + a for i, a in zip(reversed(xrange(n)), wt)]
    return R(_vandermonde(n, l) / _vandermonde(n, reversed(range(n))))


def _vandermonde(n, wt):
    R = PolynomialRing(QQ, names=["x%s" % i for i in range(n)])
    vrs = R.gens()
    m = matrix([[x ** a for x in vrs] for a in wt])
    return m.det()


class YoungTableu(object):

    def __init__(self, n=None, col_numbers=None):
        self._n = n
        self._col_numbers = col_numbers

    @property
    def n(self):
        return self._n

    @property
    def col_numbers(self):
        return self._col_numbers

    def row_numbers(self):
        res = []
        for i in range(self.n):
            res.append([c[i] for c in self.col_numbers if len(c) > i])
        return res

    def weight(self):
        return [len(l) for l in self.row_numbers()]

    def __repr__(self):
        return "\n".join(str(a) for a in self.row_numbers())


def _increasing_nums(n, m, lower_bds=None):
    '''
    n, m: positive integers,
    lower_bds: list of integers of length m.
    Returns a generator of m numbers (a0, a1, ..., a_(m-1)),
    such that a0, a1, .. in [1, ..., n],
    a0 < a1 < ... a_(m-1),
    a0 >= lower_bds[0], a1 >= lower_bds[1] .. and a_(m-1) >= lower_bds[m-1].
    '''
    cmbs = combinations(range(1, n + 1), m)
    cmbs = (list(sorted(a)) for a in cmbs)
    if lower_bds is None:
        for a in cmbs:
            yield a
    else:
        for a in cmbs:
            if all(x >= y for x, y in zip(a, lower_bds)):
                yield a


def semistandard_young_tableaux(n, wt):
    '''Returns a generator of semistandard Young tableaux.
    '''
    wt_rvsd = list(reversed(wt))
    wt_df = [wt_rvsd[0]] + [wt_rvsd[i + 1] - wt_rvsd[i] for i in range(n - 1)]
    col_lngs = reduce(
        lambda x, y: x + y, [[l] * a for l, a in zip(reversed(range(1, n + 1)), wt_df)])

    def _prod(col_lngs):
        if len(col_lngs) == 1:
            for a in _increasing_nums(n, col_lngs[0]):
                yield [a]
        else:
            for b in _prod(col_lngs[:-1]):
                for c in _increasing_nums(n, col_lngs[-1], lower_bds=b[-1]):
                    yield list(b) + [c]

    for a in _prod(col_lngs):
        yield YoungTableu(n=n, col_numbers=a)


def _index_of_gamma_0_gl_n(alphas, p):
    '''
    Returns delta(a1, ..., an) defined in Shimura, Euler products and Eisenstein
    series, pp 118, (15.1.7).
    '''
    if p in ZZ:
        p = ZZ(p)

    def _bn(n):
        return mul(1 - p ** (-i) for i in xrange(1, n + 1))

    e_r_ls = [(k, len(list(v)))
              for k, v in groupby(sorted(alphas), lambda x: x)]
    res = _bn(len(alphas)) / mul(_bn(r) for _, r in e_r_ls)
    for i, (ei, ri) in enumerate(e_r_ls):
        for j, (ej, rj) in enumerate(e_r_ls):
            if i < j:
                res *= p ** ((ej - ei) * ri * rj)
    return res
