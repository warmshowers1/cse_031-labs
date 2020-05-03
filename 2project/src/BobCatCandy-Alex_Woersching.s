	.data 
str0: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!\nPlease enter the price of a Bobcat Bar: \n"
qwraps: .asciiz "Please enter the number of wrappers needed to exchange for a new bar: \n"
qmoney: .asciiz "How much money do you have?: \n"
calc: .asciiz "Good! Let me run the number ... \n"
first: .asciiz "You first buy "
then: .asciiz "Then, you will get another "
bars: .asciiz " bars.\n"
end1: .asciiz "With $"
end2: .asciiz ", you will receive a maximum of "
end3: .asciiz " Bobcat Bars!\n"
nope: .asciiz "This input was unmanageable, the program was terminated.\n"
    	.text

main:		addi $sp, $sp -4
		sw $ra, 4($sp)
		
		la $a0, str0
		li $v0, 4
		syscall	# "Welcome to BobCat Candy, home to the famous BobCat Bars!\nPlease enter the price of a Bobcat Bar: "
		li $v0, 5
		syscall # Input
		move $a1, $v0	# $a1 = price
		add $t0, $a1, $0
		bgt $t0, $0, inw	# If the price <= 0, end the program immediately
		la $a0, nope
		li $v0, 4
		syscall
		j end
inw:		la $a0, qwraps
		li $v0, 4
		syscall	# "Please enter the number of wrappers needed to exchange for a new bar: "
		li $v0, 5
		syscall # Input
		move $a2, $v0	# $a2 = n
		addi $t0, $a2, -1
		bgt $t0, $0, inm	# If n <= 1, end the program immediately
		la $a0, nope
		li $v0, 4
		syscall
		j end
inm:		la $a0, qmoney
		li $v0, 4
		syscall	# "How much money do you have?: "
		li $v0, 5
		syscall	# Input
		move $a3, $v0	# $a3 = money
		la $a0, calc
		li $v0, 4
		syscall	# "Good! Let me run the number ... \n"
		
		jal maxBars 	# Call maxBars to calculate the maximum number of BobCat Bars
		
		# Print out final statement here
		la $a0, end1
		li $v0, 4
		syscall	# "With $"
		move $a0, $a3
		li $v0, 1
		syscall	# [Initial money amount]
		la $a0, end2
		li $v0, 4
		syscall	# ", you will receive a maximum of "
		move $a0, $v1	# Notice I'm storing the final value in $v1, not $v0
		li $v0, 1
		syscall	# [Max bars purchased]
		la $a0, end3
		li $v0, 4
		syscall	# " Bobcat Bars!\n"

		j end			# Jump to end of program

maxBars:	addi $sp, $sp, -4
		sw $ra, 4($sp)
		# This function calculates the maximum number of BobCat Bars.
		# It takes in 3 arguments ($a1, $a2, $a3) as price, n, and money. It returns the maximum number of bars
		div $a3, $a1
		mflo $a1
		# a1 = Bars that can be BOUGHT
		# a2 = n
		bgez $a1, check
		li $a1, 0
		j noprint
		
check:		sw $a1, 0($sp)
		la $a0, first	
		li $v0, 4
		syscall	# "You first buy "
		move $a0, $a1
		li $v0, 1
		syscall	# [money / price]
		la $a0, bars
		li $v0, 4
		syscall	# " bars.\n"
		
noprint:	jal newBars 	# Call a helper function to keep track of the number of bars.
		
		lw $t0, 0($sp)
		add $v1, $v1, $t0
		
		lw $ra, 4($sp)
		jr $ra
		# End of maxBars

newBars:	addi $sp, $sp -8
		sw $ra, 4($sp)
		# This function calculates the number of BobCat Bars a user will receive based on n.
		# It takes in 2 arguments ($a1, $a2) as number of wrappers left so far and n.
		div $a1, $a2
		mflo $a1
		beq $a1, $0, pop
		
        	# Prints the number of bars you can receive
		la $a0, then
		li $v0, 4
		syscall # "Then, you will get another "
		move $a0, $a1
		li $v0, 1
		syscall # [print number of bars]
		la $a0, bars
		li $v0, 4
		syscall # " bars.\n"

        	mfhi $t0	# Pull the remaining wrappers that couldn't be exchanged and save them for later. 
		sw $a1, 0($sp)	# Save the number of bars you would receive to the stack. 
		add $a1, $a1, $t0	# Add the left over wrappers to this register to make it now represent the total number of wrappers you currently have, this will be passed as a parameter when we recursively call newBars. 
		jal newBars
		
		lw $t0, 0($sp)
		add $v1, $v1, $t0
		
pop:		lw $ra, 4($sp)
		addi $sp, $sp, 8
		jr $ra
		
end: 		addi $sp, $sp 4
		li $v0, 10 
		syscall