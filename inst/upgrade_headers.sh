CMDSTAN_VER="2.33.1"

wget https://github.com/stan-dev/cmdstan/releases/download/v$CMDSTAN_VER/cmdstan-$CMDSTAN_VER.tar.gz
tar -xf cmdstan-$CMDSTAN_VER.tar.gz
rm -rf include/cmdstan
rm -rf include/stan
rm -rf include/sundials
mkdir -p include

cp -r cmdstan-$CMDSTAN_VER/src/cmdstan include/cmdstan
cp -r cmdstan-$CMDSTAN_VER/stan/src/stan include/stan
cp -r cmdstan-$CMDSTAN_VER/stan/lib/stan_math/stan/math include/stan/math
cp -r cmdstan-$CMDSTAN_VER/stan/lib/stan_math/stan/math.hpp include/stan/math.hpp

cp -r cmdstan-$CMDSTAN_VER/stan/lib/stan_math/lib/opencl**/CL include/CL

mv include/stan/math/opencl include/opencl
grep -rl stan/math/opencl include/cmdstan | xargs gsed -i 's/stan\/math\/opencl/opencl/g'
grep -rl stan/math/opencl include/stan | xargs gsed -i 's/stan\/math\/opencl/opencl/g'
grep -rl stan/math/opencl include/opencl | xargs gsed -i 's/stan\/math\/opencl/opencl/g'

cp -r cmdstan-$CMDSTAN_VER/stan/lib/stan_math/lib/sundials_*/include include/sundials
cp -r cmdstan-$CMDSTAN_VER/stan/lib/stan_math/lib/sundials_*/src ../src/sundials

gsed -i -e 's/std::cout/Rcpp::Rcout/g' include/cmdstan/command.hpp
gsed -i -e 's/std::cerr/Rcpp::Rcerr/g' include/cmdstan/command.hpp
gsed -i -e 's/std::cerr/Rcpp::Rcerr/g' include/cmdstan/command_helper.hpp

# Gives -Woverflow errors under windows
gsed -i -e 's/const unsigned long prime/const unsigned long long prime/g' ../src/sundials/sundials/sundials_hashmap.h
gsed -i -e 's/unsigned long hash/unsigned long long hash/g' ../src/sundials/sundials/sundials_hashmap.h


rm cmdstan-$CMDSTAN_VER.tar.gz
rm -rf cmdstan-$CMDSTAN_VER
