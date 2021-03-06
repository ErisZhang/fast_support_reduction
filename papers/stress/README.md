## Terminologies


+ constitutive equation
    + https://en.wikipedia.org/wiki/Constitutive_equation

+ stress
    + https://en.wikipedia.org/wiki/Stress_(mechanics)
    + _stress_ (sigma) is a physical quantity that expresses the internal forces that neighbouring particles of a continuous material exert on each other
        + stress exceeding strength limit of material will result in permanent deformation (fracture) of material
        + _definition_: force across a "small" boundary per unit area of that boundary, for all orientations of the boundary.
    + _strain_ is the measure of the deformation of the material. 
        + generates internal elastic stress


+ linear elasticity
    + https://en.wikipedia.org/wiki/Linear_elasticity
    + how solid objects deform and become internally stressed due to prescribed loading conditions.
    + assumptions
        + small deformations (strains)
        + linear relationship between strain and stress
    + problem
        + boundary value problem based on 3 tensor PDE


+ intro to elasticity/constitutive relations
    + https://en.wikiversity.org/wiki/Introduction_to_Elasticity/Constitutive_relations#Isotropic_materials
    + elasticity
        + strain-displacement relation
        + traction-stress relation
        + balance laws for linear and angular momentum in terms of stress
        + constitutive (stress-strain) equation
    + constitutive relation
        + isotropic elasticity


+ direct stiffness method 
    + https://en.wikipedia.org/wiki/Direct_stiffness_method


+ MIT 16.20 structural mechanics
    + http://web.mit.edu/16.20/homepage/index.html


## textbooks & learning resources


+ [text_2009_structural_analysis_with_applications_to_aerospace_structures](text_2009_structural_analysis_with_applications_to_aerospace_structures.pdf)
    + great book on introducing basic concepts in linear elasticity theory
    + chapter 1-4, skip special case analytic solution procedures
    + but did not provide enough detail on FEM to solve the stress field

+ [text_2002_the_linearized_theory_of_elasticity](text_2002_the_linearized_theory_of_elasticity.pdf)
    + pretty math intensive, but quite expressive and clean (tensor notation mostly)
    + didn't really talk about how to solve linear elasticity equation using FEM

+ [text_2010_the_finite_element_method_theory_implementation_and_practice](text_2010_the_finite_element_method_theory_implementation_and_practice.pdf)
    + details on FEM
    + chapter 11 specifically on FEM on linear elasticity problems
    + accompanying assignment: http://www.it.uu.se/edu/course/homepage/finmet2/vt14/material/proj1.pdf

+ siggraph 2012 course in FEM and structural analysis [part1](siggraph_2012_part1_classical_fem_method_and_discretization_methodology.pdf) and [part2](siggraph_2012_part2_model_reduction.pdf)



## papers

+ [2012_stress_relief_improving_structural_strength_of_3D_printable_objects](2012_stress_relief_improving_structural_strength_of_3D_printable_objects.pdf)
    + abstract 
        + automatic detection and correction of problematic cases for 3D printing objects to make more "structurally sound" while retaining visual similarity
        + idea
            + find high structural stress positions
            + remediate with 
                + hollowing (weights)
                + thickening (increases strength of thin)
                + struct insertion (prevent nonrigid deformation)
        + steps
            + 
    + 1 related work/paper
        + paper on structurally stable method by modifying shape to minimize a certain objective function
    + 3 printability analysis
        + structural loads
            + permanent load (gravity)
                + given _default upright orientation_
                + and find additional orientations with some heuristic
            + imposed load (gravity + pinch grip)
                + 2 finger pinch (location determined with some heuristic)
        + structural analysis
            + problem: linear elasticity problem with a homogenous material
            + tet mesh 
            + discrete linear elasticity problem using FEM with quadratic tetrahedral elements
                + `Kd=F`
                    + `K` stiffness matrix
                    + `d` deformation of mesh 
                    + `F` force
                + use deformation to compute 
                    + strain: Cauchy linear strain tensor
                    + stress: hook's law
                + von mises yield criterion to determine structural problems
     


+ [2013_worst_case_structural_analysis](2013_worst_case_structural_analysis.pdf)
    + abstract
        + identify structural problems in 3D printing objects based on _geometry_ and _material property_ only, without assumptions on loads.
        + idea
            + constrained optimization to determine _worst case load distribution_ for a shape that will cause high local stress or large deformations (i.e. minimal force to break it or severely deform it)
            + approximate method to make it run faster
    + 2 related work / paper
        + 2012 paper finds structural weakness considering gravity loads and gripping shape with 2 fingers
        + 3d printing processes
            + materials
                + brittle: need to know where material likely to break
                + ductile: need to know where material likely to be plastic
            + goal:
                + find worst case loads (that leads to maximal damage)
                    + norm of stress
                    + maximal displacements
    + 3 worst case structural analysis
        + 



+ [2016_stochastic_structural_analysis_for_context_aware_design_and_fabrication](2016_stochastic_structural_analysis_for_context_aware_design_and_fabrication.pdf)
    + goal 
        + probability of failure as a measure of reliability
    + background
        + FEM
            + tool for failure analysis 
            + drawbacks
                + spatially varying ratings not intuitive
                + worst-case scenario may never happen (in real-world use)
        + stochastic FEM
            + idea
                + assume material property fixed, apply load stochastically with unknown variance
                    + i.e. interaction of linearly elastic, infinitesimally deforming objects with the world, both persistent and transient
                    + simulated with rigid body simulation
            + compute probability of failure
                + i.e. a toy can survive 99% of interactions in real-world
            + force distribution instead of single instance of applied force
            + method
                + method of generating realistic force distributions (rigid-body physics engine generates force samples on surface) (speed by 1 order of magnitude from MC based appr)
                + SVD -> low-dim reduced force-space
                + compute failure probability density function (probability that max stress experienced by an object will exceed a given threshold)
        + inverse design problem
            + given
                + mesh
                + volumetric material assignment
                + usage scenario
                + minimum fracture probability
            + automatically correct design flaws
                + reduce weight
                + guarantee probablity of breaking less than specified value
    + 2 related work/paper
        + FEM for (worst-case) structural analysis
            + `2012_stress_relief_improving_structural_strength_of_3D_printable_objects`
            + `2013_worst_case_structural_analysis`
            + weakness map ... areas of failure
        + SFEM
            + different kinds (monte carlo/ perturbation)
        + topology optimization
            + topology of an object is optimized to meet certain requirement
    + 3 background on structural analysis
        + FEM for linearly elastic objects
            + compute stress induced on an objct by the applied force
            + steps
                + discretization with mesh of volumetric cell
                + static equilibrium `Ku=f`
                    + `u` is nodal displacement
                + stress `sigma=CBu`
                    + `sigma` is cauchy stres
        + detecting failure using yield stress
            + fracture
                + `von Mises stress > yield stress (material specific)`
        + stochastic FEM
            + `u` and `f` replaced by random variables
    + 4 fracture probabilities using SFEM
        + generate force distributions
            + assumptions
                + object deforms infinitesimally
                + object instantaneously returns to its undeformed state after a force is applied
            + goodness
                + assume geometry and inertial property fixed over time (hence can be simulated as a rigid body)