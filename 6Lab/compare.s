        .data
n:       .word 25
str1:    .asciiz "Less than"
str2:    .asciiz "Less than or equal to"
str3:    .asciiz "Greater than"
str4:    .asciiz "Greater than or equal to"

	.text

main:   li $v0, 5           # Take in user input
        syscall             # Do it
        move $t0, $v0       # Store the user input in $t0

        la $s0, n           # Store n in $s0
        lw $s0, 0($s0)

        slt $t1, $t0, $s0   # Check if $s0 < $t0, if yes: $t1 = 1, if no: $t1 = 0
        bne $t1, $0, less   # Is $t1 != 0? (is $t1 = 1?)
        j greq              # Jump to greq if $t1 = 0

less:   la $a0, str1
        #lw $a0, 0($a0)
        j finish

leq:    la $a0, str2
        #lw $a0, 0($a0)
        j finish

great:  la $a0, str3
        #lw $a0, 0($a0)
        j finish

greq:   la $a0, str4
        #lw $a0, 0($a0)
        j finish

finish: li $v0, 4
        syscall
