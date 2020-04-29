	.data 
str0: .asciiz "Welcome to BobCat Candy, home to the famous BobCat Bars!\nPlease enter the price of a Bobcat Bar: "
qwraps: .asciiz "Please enter the number of wrappers needed to exchange for a new bar: "
qmoney: .asciiz "How much money do you have?: "
calc: .asciiz "Good! Let me run the number ... \n"
nope: .asciiz ", you will receive a maximum of 0 Bobcat Bars!\n"
first: .asciiz "You first buy "
then: .asciiz "Then, you will get another "
bars: .asciiz " bars.\n"
end1: .asciiz "With $"
end2: .asciiz ", you will receive a maximum of "
end3: .asciiz " Bobcat Bars!\n"
.text

main:		addi $sp, $sp -4	# Feel free to change the increment if you need for space.
		sw $ra, 4($sp)
		# Implement your main here

		# Gets user input and stores the values in appropriate registers
		la $a0, str0
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $a1, $v0
		la $a0, qwraps
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $a2, $v0
		la $a0, qmoney
		li $v0, 4
		syscall
		li $v0, 5
		syscall
		move $a3, $v0
		# $a1 = price
		# $a2 = n
		# $a3 = money
		la $a0, calc
		li $v0, 4
		syscall
		
		jal maxBars 	# Call maxBars to calculate the maximum number of BobCat Bars
		
		# Print out final statement here
		la $a0, end1
		li $v0, 4
		syscall
		move $a0, $a3
		li $v0, 1
		syscall
		la $a0, end2
		li $v0, 4
		syscall
		move $a0, $v1		# Notice I'm storing the final value in $v1, not $v0
		li $v0, 1
		syscall
		la $a0, end3
		li $v0, 4
		syscall

		j end			# Jump to end of program



maxBars:	addi $sp, $sp, -4
		sw $ra, 4($sp)
		# This function calculates the maximum number of BobCat Bars.
		# It takes in 3 arguments ($a1, $a2, $a3) as price, n, and money. It returns the maximum number of bars
		div $a3, $a1
		mflo $a1
		# a1 = Bars that can be BOUGHT
		# a2 = n
		blez $a1, nobuy # Jump to nobuy if they don't have enough money
		sw $a1, 0($sp)
		
		la $a0, first
		li $v0, 4
		syscall
		move $a0, $a1
		li $v0, 1
		syscall
		la $a0, bars
		li $v0, 4
		syscall
		
		
		jal newBars 	# Call a helper function to keep track of the number of bars.
		
		lw $t0, 0($sp)
		add $v1, $v1, $t0
		
		lw $ra, 4($sp)
		jr $ra
		# End of maxBars

newBars:	addi $sp, $sp -12
		sw $ra, 8($sp)
		# This function calculates the number of BobCat Bars a user will receive based on n.
		# It takes in 2 arguments ($a1, $a2) as number of wrappers left so far and n.
		div $a1, $a2
		mflo $a1
		beq $a1, $0, pop
		
		la $a0, then
		li $v0, 4
		syscall
		move $a0, $a1
		li $v0, 1
		syscall
		la $a0, bars
		li $v0, 4
		syscall
		
		sw $a1, 4($sp)
		jal newBars
		
		lw $t0, 4($sp)
		add $v1, $v1, $t0
		# End of newBars
		
pop:		lw $ra, 8($sp)
		addi $sp, $sp, 12
		jr $ra

nobuy:		# "With $ [$a3], you will receive a maximum of 0 Bobcat bars!"
		la $a0, end1
		li $v0, 4
		syscall
		move $a0, $a3
		li $v0, 1
		syscall
		la $a0, nope
		li $v0, 4
		syscall
		j end
end: 
		# Terminating the program
		lw $ra, 0($sp)
		addi $sp, $sp 4
		li $v0, 10 
		syscall
