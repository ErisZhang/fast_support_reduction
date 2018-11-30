#include <Eigen/Core>

#include <igl/readMESH.h>
#include <igl/readOBJ.h>
#include <igl/readDMAT.h>
#include <igl/readTGF.h>
#include <igl/slice.h>
#include <igl/jet.h>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/normalize_row_sums.h>

#include "src/defs.h"
#include "src/reduce_support.h"
#include "src/minitrace.h"

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace Eigen;

int main(int argc, char*argv[]) {

    using namespace Eigen;
    using namespace std;
    mtr_init("build/trace.json");

    std::string filename = "woody";
    int pso_iters = 1;
    int pso_population = 1;
    double c_arap = 1;
    double c_overhang = 1;
    double c_intersect = 1;
    double rotation_angle = M_PI / 10;

    if (argc == 2) {
        filename = argv[1];
    }
    if (argc == 3) {
        pso_iters = std::stoi(argv[1]);
        pso_population = std::stoi(argv[2]);
    }
    if (argc == 4) {
        filename = argv[1];
        pso_iters = std::stoi(argv[2]);
        pso_population = std::stoi(argv[3]);
    }
    if (argc == 8) {
        filename = argv[1];
        pso_iters = std::stoi(argv[2]);
        pso_population = std::stoi(argv[3]);
        rotation_angle = (std::stod(argv[4]) / 180.) * M_PI / 2;
        c_arap = std::stod(argv[5]);
        c_overhang = std::stod(argv[6]);
        c_intersect = std::stod(argv[7]);
    }

    bool is3d = (filename.find("woody") == 0 || filename.find("thin") == 0) ? 
        false : true;

    Eigen::MatrixXf V, U;
    Eigen::MatrixXi E, F;   // E=element

    if (is3d) {
        igl::readMESH(DATA_PATH+filename+".mesh", V, E, F);
    } else {
        igl::readOBJ(DATA_PATH+filename+".obj", V, F);
    }
    U = V;

    Eigen::MatrixXf W;
    igl::readDMAT(DATA_PATH+filename+".dmat", W);
    // do normalization before lbs
    igl::normalize_row_sums(W, W);

    Eigen::MatrixXd Cd;
    Eigen::MatrixXf C;
    Eigen::MatrixXi BE;
    igl::readTGF(DATA_PATH+filename+".tgf", Cd, BE);
    C = Cd.cast<float>();

    ReduceSupportConfig config;
    config.is3d = is3d;
    config.alpha_max = 0.25 * M_PI;
    config.dp = Eigen::RowVector3f(0., 1., 0.);
    config.rotation_angle = rotation_angle;
    config.pso_iters = pso_iters;
    config.pso_population = pso_population;
    config.c_arap = c_arap;
    config.c_overhang = c_overhang;
    config.c_intersect = c_intersect;
    config.display = true;

    Eigen::MatrixXf T;
    // reduce_support(V, F, C, BE, W, config, T, U);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    int selected = 0;
    const Eigen::RowVector3d sea_green(70./255.,252./255.,167./255.);
    igl::opengl::glfw::Viewer viewer;
    const auto set_color = [&](igl::opengl::glfw::Viewer &viewer) {
        Eigen::MatrixXd Color;
        igl::jet(W.col(selected).eval(),true,Color);
        viewer.data().set_colors(Color);
    };
    set_color(viewer);
    viewer.data().set_mesh(U.cast<double>(), F);
    viewer.data().set_edges(C.cast<double>(),BE,sea_green);
    viewer.data().show_lines = false;
    viewer.data().show_overlay_depth = false;
    viewer.data().line_width = 1;
    viewer.callback_key_down = 
        [&](igl::opengl::glfw::Viewer &, unsigned char key, int mod) {
            switch(key) {
                case '.':
                    selected++;
                    selected = std::min(std::max(selected,0),(int)W.cols()-1);
                    set_color(viewer);
                    break;
                case ',':
                    selected--;
                    selected = std::min(std::max(selected,0),(int)W.cols()-1);
                    set_color(viewer);
                    break;
            }
            return true;
        };
    cout<<
    "Press '.' to show next weight function."<<endl<<
    "Press ',' to show previous weight function."<<endl<<
    viewer.launch();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////


    mtr_flush();
    mtr_shutdown();
}