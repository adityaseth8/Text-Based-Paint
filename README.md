# Text-Based-Paint

As part of my Programming & Problem Solving (ECS 36A) class, we had to create a text-based version of paint coded in C. Features implemented include quit, help, write, add, delete, resize, save, and load. Technical concepts embedded include pointers, structs, optional command line parameters, and make files. To compile, download the files included and type "make" in the compiler. The program accepts optional command line parameters which specify the canvas size. So you may start off with just "./paint.out", which would yield a standard 10 by 10 board. Or you may start the paint game by typing "./paint.out" + number of rows + number of columns. After that, you may use the following commands:

Help: h <br />
Quit: q <br />
Draw line: w row_start col_start row_end col_end <br />
Resize: r num_rows num_cols <br />
Add row or column: a [r | c] pos <br />
Delete row or column: d [r | c] pos <br />
Erase: e row col <br />
Save: s file_name <br />
Load: l file_name <br />

Project completed in Dec 2021.
