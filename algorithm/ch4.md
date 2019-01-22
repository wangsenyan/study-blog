## 分治算法

* Strassen(A,B)

```
if A.length == 1 then
return A[1] · B[1]
end if
Let C be a new n by n matrix
A11 = A[1..n/2][1..n/2]
A12 = A[1..n/2][n/2 + 1..n]
A21 = A[n/2 + 1..n][1..n/2]
A22 = A[n/2 + 1..n][n/2 + 1..n]
B11 = B[1..n/2][1..n/2]
B12 = B[1..n/2][n/2 + 1..n]
B21 = B[n/2 + 1..n][1..n/2]
B22 = B[n/2 + 1..n][n/2 + 1..n]
S1 = B12 − B22
S2 = A11 + A12
S3 = A21 + A22
S4 = B21 − B11
S5 = A11 + A22
S6 = B11 + B22
S7 = A12 − A22
S8 = B21 + B22
S9 = A11 − A21
S10 = B11 + B12
P1 = Strassen(A11, S1)
P2 = Strassen(S2, B22)
P3 = Strassen(S3, B11)
P4 = Strassen(A22, S4)
P5 = Strassen(S5, S6)
P6 = Strassen(S7, S8)
P7 = Strassen(S9, S10)
C[1..n/2][1..n/2] = P5 + P4 − P2 + P6
C[1..n/2][n/2 + 1..n] = P1 + P2
C[n/2 + 1..n][1..n/2] = P3 + P4
C[n/2 + 1..n][n/2 + 1..n] = P5 + P1 − P3 − P7
return C
```