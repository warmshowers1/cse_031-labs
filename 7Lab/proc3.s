        .data
x:      .word 5
y:      .word 10

        .text
main:   la $t0, x
        lw $s0, 0($t0) # $s0 = x
        la $t0, y
        lw $s1, 0($t0) # $s1 = y

        add $a0, $zero, $s0
        add $a1, $zero, $s1
        addi $sp, $sp, -4
        sw $s0, 4($sp)
        sw $s1, 0($sp)
        jal sum

        lw $s0, 4($sp)
        lw $s1, 0($sp)
        add $s1, $s1, $s0   # y = y + x ...
        add $a0, $s1, $v0   # $a0 = y + sum($s0, $s1)
        addi $v0, $zero, 1
        syscall
        j end

sum:    addi $sp, $sp, -12
        # Save all values for later
        sw $a0, 8($sp)
        sw $a1, 4($sp)
        sw $ra, 0($sp)

        # Prepare registers $a0 & $a1 to pass through sub()
        addi $a0, $a1, 1
        lw $t0, 8($sp)
        addi $a1, $t0, 1
        jal sub
        add $s0, $zero, $v1 # Store value returned from sub() in $s0

        # Restore the original values passed into sum()
        lw $a0, 8($sp)
        lw $a1, 4($sp)

        # Prepare registers $a0 & $a1 to pass through sub()
        addi $a0, $a0, -1
        addi $a1, $a1, -1
        jal sub
        add $s1, $zero, $v1 # Store value returned from sub() in $s1

        add $v0, $s0, $s1   # p + q
        lw $ra, 0($sp)      # Restore the original return address to get back to main()
        addi $sp, $sp, 12   # Move stack pointer back for convenience
        jr $ra              # Jump back to main()

sub:    sub $v1, $a1, $a0   # Subtract $a0 from $a1 and store them in $v1
        jr $ra              # Return

end:
