        .data
ask:    .asciiz "Please enter a number: "
psum:   .asciiz "Sum of positive numbers is: "
nsum:   .asciiz "Sum of negative numbers is: "
nl:	    .asciiz "\n"

        .text
loop:   li $v0, 4           # Set syscall to print a string
	    la $a0, ask	        # Load ask string into correct register
	    syscall             # Print
        li $v0, 5           # Set syscalls to ask for user input
        syscall             # Ask
        move $t0, $v0       # Move input value to more convenient location ($t0)
        beq $t0, $0, finish # If the input was equal to 0, finish the program
        slt $t1, $0, $t0    # Check if the input is greater than 0
        beq $t1, $0, neg    # If $t0 < 0: jump to neg, else keep going (positive)

        add $s0, $s0, $t0   # Add the value to the sum total register $s0 (positive reg)
        j loop              # Jump to beginning of loop

neg:    add $s1, $s1, $t0   # Add the value to the sum total register $s1 (negative reg)
        j loop              # Jump to beginning of loop

finish: li $v0, 4           # Set syscall to print a string
        la $a0, psum        # Load psum string into correct register
        syscall             # Print
        li $v0, 1           # Set syscalls to print an integer
        add $a0, $s0, $0    # Set the correct register to the positive sum register ($s0)
        syscall             # Print
        li $v0, 4	        # Set syscall to print a string
        la $a0, nl	        # Load nl string into correct register
        syscall		        # Print
        
        li $v0, 4           # Set syscall to print a string
        la $a0, nsum        # Load nsum string into correct register
        syscall             # Print
        li $v0, 1           # Set syscalls to print an integer
        add $a0, $s1, $0    # Set the correct register to the negative sum register ($s1)
        syscall             # Print
        li $v0, 4	        # Set syscall to print a string
        la $a0, nl	        # Load nl string into correct register
        syscall		        # Print
