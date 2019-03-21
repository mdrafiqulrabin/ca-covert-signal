# CA-Covert-Signal
Programming Assignment: 2019SP-COSC6385-Computer Architecture \
Task: Timing of the branch code block in the spy process, reflecting the data sent by the trojan.

- - -

# Guidelines:

- Study the paper "Covert Channels Through Branch Predictors" paper published in HASP'15 by Evtyushkin et al.
- This assignment is about Figure 3: Timing of the branch code block in the spy process, reflecting the data sent by the trojan.
- Implement the spy/trojan process:
  - Add detailed steps to run the code in Linux system.
  - Describe the result with a sample message passing and timing plots.

- - -

# Steps:

1. First, execute the following command to generate the asm branch for trojan/spy program:
    ```
    $ python asm_branch.py
    ```

2. Then, execute the following commands to compile trojan/spy program:
    ```
    $ gcc -masm=intel -ggdb trojan.c -o t.out -lpthread
    $ gcc -masm=intel -ggdb spy.c -o s.out -lpthread
    ```
    In this stage, two executable files "t.out" and "s.out" will be generated.

3. Now, execute the following commands to run trojan/spy program:
    ```
    $ ./t.out "msg"
    $ ./s.out
    ```
    Note: Trojan/Spy program must be run on the same cpu core to get the effect of branch history table. When executing the "s.out", it will save the iteration times and cycles into "cycles_times.log" for MAX_PROBES. 

4. Finally, run the "draw_plot.py", it will save the plot of cycles vs iteration times for latest run as "cycles_times.png".
    ```
    $ python draw_plot.py
    ```

- - -

# Fig. #3: Covert Channels

<img src="https://github.com/mdrafiqulrabin/ca-covert-signal/blob/main/results/cycles_times.png" alt="spy/trojan" width="600"/>

- - -

# References:

- Covert Channels Through Branch Predictors: https://dl.acm.org/doi/10.1145/2768566.2768571
- The Linux Programming Interface: https://man7.org/tlpi/

