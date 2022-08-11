# CMakeList.txt: HSSPRCAL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("HSSPRCAL")

# 将源代码添加到此项目的可执行文件。
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable (
	HSSPRCAL
	"source/basic.cpp" "source/basic.h"
	"source/offer.cpp" "source/offer.h"
	"source/trans.cpp" "source/trans.h"
	"source/output.cpp" "source/output.h"
	"source/formula.cpp" "source/formula.h"
	"source/solve_refresh.cpp" "source/solve_refresh.h"
	"source/gen.cpp" "source/gen.h"
	"source/pre.cpp" "source/pre.h"
	"source/auto.h" "source/auto.cpp"
	"source/ui.cpp" "source/ui.h"
	"source/HSSPRCAL_W.cpp"
  )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_FLAGS "-O3")
  add_executable (
	HSSPRCAL
	"source/basic.cpp" "source/basic.h"
	"source/offer.cpp" "source/offer.h"
	"source/trans.cpp" "source/trans.h"
	"source/output.cpp" "source/output.h"
	"source/formula.cpp" "source/formula.h"
	"source/solve.cpp" "source/solve.h"
	"source/gen.cpp" "source/gen.h"
	"source/pre.cpp" "source/pre.h"
	"source/HSSPRCAL_L.cpp"
  )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HSSPRCAL PROPERTY CXX_STANDARD 11)
endif()

# TODO: 如有需要，请添加测试并安装目标。
