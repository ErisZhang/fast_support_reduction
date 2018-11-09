

```
git clone --recursive git@github.com:tt6746690/fast_support_reduction.git
```


#### TODO

+ fix bbw for 2D case
+ confirm with alec/oded on if its possible to derive closed form solution for 3 energy term
    + and then make the derivation 

+ look at mashoya for global optimization procedure
+ explore global optimization
+ list energy terms


#### API 


+ https://github.com/libigl/libigl/blob/master/include/igl/directed_edge_parents.h
+ https://github.com/libigl/libigl/blob/master/include/igl/harmonic.h
+ https://github.com/libigl/libigl/blob/master/include/igl/bbw.h
+ https://github.com/libigl/libigl/blob/master/include/igl/lbs_matrix.h


+ formats
    + `dmat`: human readable eigen matrix
    + `tfg`: handles for deformation
    + `off`: mesh, i.e. `(V,F)`
    + `obj`: mesh from ascii obbj file, vertex, normal, texture, 
    + `mesh`: tetrahedron mesh  loads `V,T,F` 
        + vertices `(,3)` (7234)
        + tets `(,4)` (29998)
        + faces `(,3)` (9556)