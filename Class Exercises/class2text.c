#====================================================
# Assembly Language for Integer Arithmetic Operations
# CS281 Fall 2015
# James Le
#====================================================

   0x0804841d <+0>:	push   %ebp                      # Prologue
   0x0804841e <+1>:	mov    %esp,%ebp                 #
   0x08048420 <+3>:	and    $0xfffffff0,%esp          #
   0x08048423 <+6>:	sub    $0x10,%esp                # End of prologue
   0x08048426 <+9>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x0804842c <+15>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]
   
   0x08048431 <+20>:	add    %edx,%eax                 # %eax <- %eax + %edx
   0x08048433 <+22>:	mov    %eax,0x804a030            # store the sum value into %eax
   0x08048438 <+27>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x0804843e <+33>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]

   0x08048443 <+38>:	sub    %eax,%edx                 # %edx <- %edx - %eax
   0x08048445 <+40>:	mov    %edx,%eax                 # %eax <- %eax
   0x08048447 <+42>:	mov    %eax,0x804a030            # store the difference value into %eax
   0x0804844c <+47>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x08048452 <+53>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]

   0x08048457 <+58>:	imul   %edx,%eax                 # %eax <- %eax * %edx 
   0x0804845a <+61>:	mov    %eax,0x804a030            # store the multiplication value into %eax
   0x0804845f <+66>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x08048465 <+72>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]

   0x0804846a <+77>:	xor    %edx,%eax                 # %eax <- %eax ^ %edx
   0x0804846c <+79>:	mov    %eax,0x804a030            # store the Exclusive-OR value into %eax
   0x08048471 <+84>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x08048477 <+90>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]

   0x0804847c <+95>:	or     %edx,%eax                 # %eax <- %eax | %edx
   0x0804847e <+97>:	mov    %eax,0x804a030            # store the OR value into %eax
   0x08048483 <+102>:	mov    0x804a020,%edx            # %edx <- M[0x804a020]
   0x08048489 <+108>:	mov    0x804a024,%eax            # %eax <- M[0x804a024]

   0x0804848e <+113>:	and    %edx,%eax                 # %eax <- %eax & %edx
   0x08048490 <+115>:	mov    %eax,0x804a030            # store the AND value into %eax
   0x08048495 <+120>:	mov    0x804a020,%eax            # %eax <- M[0x804a020]

   0x0804849a <+125>:	neg    %eax                      # %eax <- -%eax
   0x0804849c <+127>:	mov    %eax,0x804a030            # store the negation value into %eax
   0x080484a1 <+132>:	mov    0x804a020,%eax            # %eax <- M[0x804a020]

   0x080484a6 <+137>:	not    %eax                      # %eax <- ~%eax
   0x080484a8 <+139>:	mov    %eax,0x804a030            # store the complement value into %eax
   0x080484ad <+144>:	mov    0x804a020,%eax            # %eax <- M[0x804a020]

   0x080484b2 <+149>:	lea    0x1(%eax),%edx            # %edx <- 1 + %eax (compute the address of the operand)
   0x080484b5 <+152>:	mov    %edx,0x804a020            # M[0x804a020] <- %edx
   0x080484bb <+158>:	mov    %eax,0x804a030            # store the Load Effective Address value into %eax
   0x080484c0 <+163>:	mov    0x804a020,%eax            # %eax <- M[0x804a020]

   0x080484c5 <+168>:	sar    $0x2,%eax                 # %eax <- %eax >>= 2 (Arithmetically)
   0x080484c8 <+171>:	mov    %eax,0x804a030            # store the right shift value into %eax
   0x080484cd <+176>:	mov    0x804a02c,%eax            # %eax <- M[0x804a02c]

   0x080484d2 <+181>:	shr    $0x2,%eax                 # %eax <- %eax >>= 2 (Logically)
   0x080484d5 <+184>:	mov    %eax,0x804a030            # store the right shift value into %eax
   0x080484da <+189>:	mov    0x804a030,%edx            # %edx <- M[0x804a030]
   0x080484e0 <+195>:	mov    0x804a030,%eax            # %eax <- M[0x804a030]

   0x080484e5 <+200>:	mov    %edx,0x8(%esp)            # M[%esp + 8] <- %edx  ; arg2
   0x080484e9 <+204>:	mov    %eax,0x4(%esp)            # M[%esp + 4] <- %eax  ; arg1
   0x080484ed <+208>:	movl   $0x8048590,(%esp)         # store the arguments
   0x080484f4 <+215>:	call   0x80482f0 <printf@plt>    # printf(args)
   0x080484f9 <+220>:	mov    $0x0,%eax                 #
   0x080484fe <+225>:	leave                            #
   0x080484ff <+226>:	ret                              # return

