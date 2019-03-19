tjn_limit = 500000
spy_limit = 30000
filename = "asm_branch.h"
open(filename, 'w').close()

# trojan br_taken
with open(filename, 'a') as the_file:
    the_file.write("void t_br_taken() {\n")
    the_file.write("__asm__ (\n")
    the_file.write("\"mov eax, 1;\"\n")
    for i in range(0, tjn_limit):
        the_file.write("\"cmp eax, 0;\"\n")
        the_file.write("\"jne .TBT" + str(i) + ";\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\"clc; clc; clc;\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\".TBT" + str(i) + ":\"\n")
    the_file.write("\"nop; clc; nop;\"\n")
    the_file.write(");\n")
    the_file.write("}\n")
    the_file.write("\n")

# trojan br_not_taken
with open(filename, 'a') as the_file:
    the_file.write("void t_br_not_taken() {\n")
    the_file.write("__asm__ (\n")
    the_file.write("\"mov eax, 1;\"\n")
    for i in range(0, tjn_limit):
        the_file.write("\"cmp eax, 0;\"\n")
        the_file.write("\"je .TBNT" + str(i) + ";\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\"clc; clc; clc;\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\".TBNT" + str(i) + ":\"\n")
    the_file.write("\"nop; clc; nop;\"\n")
    the_file.write(");\n")
    the_file.write("}\n")
    the_file.write("\n")

# spy br_taken
with open(filename, 'a') as the_file:
    the_file.write("void s_br_taken() {\n")
    the_file.write("__asm__ (\n")
    the_file.write("\"mov eax, 1;\"\n")
    for i in range(0, spy_limit):
        the_file.write("\"cmp eax, 0;\"\n")
        the_file.write("\"jne .SBT" + str(i) + ";\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\"clc; clc; clc;\"\n")
        the_file.write("\"nop; nop; nop;\"\n")
        the_file.write("\".SBT" + str(i) + ":\"\n")
    the_file.write("\"nop; clc; nop;\"\n")
    the_file.write(");\n")
    the_file.write("}\n")
    the_file.write("\n")
