# CMakeList.txt: HSSPRCAL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("HSSPRCAL")

# 将源代码添加到此项目的可执行文件。
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable (
	HSSPRCAL
	"basic.cpp" "basic.h"
	"offer.cpp" "offer.h"
	"trans.cpp" "trans.h"
	"output.cpp" "output.h"
	"formula.cpp" "formula.h"
	"solve.cpp" "solve.h"
	"gen.cpp" "gen.h"
	"pre.cpp" "pre.h"
	"auto.h" "auto.cpp"
	"ui.cpp" "ui.h"
	"HSSPRCAL_W.cpp"
   )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_executable (
	HSSPRCAL
	"basic.cpp" "basic.h"
	"offer.cpp" "offer.h"
	"trans.cpp" "trans.h"
	"output.cpp" "output.h"
	"formula.cpp" "formula.h"
	"solve.cpp" "solve.h"
	"gen.cpp" "gen.h"
	"pre.cpp" "pre.h"
	"HSSPRCAL_L.cpp"
  )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HSSPRCAL PROPERTY CXX_STANDARD 11)
endif()

# TODO: 如有需要，请添加测试并安装目标。
