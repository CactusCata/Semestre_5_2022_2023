all:
	./launch.sh

test: all

	# Basics
	./mygrep "a" "a"
	./mygrep "a" "aaaaa"
	./mygrep "a" ""

	# Test de concaténation
	./mygrep "ab" "a"
	./mygrep "ab" "b"
	./mygrep "ab" "aaaaa"
	./mygrep "ab" "bbbbbbb"
	./mygrep "ab" "aaaab"
	./mygrep "ab" "ab"
	./mygrep "abc" "abbc"
	./mygrep "abc" "abc"
	./mygrep "aaa" "a"
	./mygrep "aaa" "aaaaa"
	./mygrep "aaa" "aaa"

	# Test d'union
	./mygrep "a+b" "a"
	./mygrep "a+b" "b"
	./mygrep "a+b" "ab"
	./mygrep "a+b" "abbabaa"
	./mygrep "a+b+c" "a"
	./mygrep "a+b+c" "b"
	./mygrep "a+b+c" "c"

	# Test des parenthèses
	./mygrep "(a+b)c" "a"
	./mygrep "(a+b)c" "ac"
	./mygrep "(a+b)c" "ab"
	./mygrep "(a+b)c" "abc"
	./mygrep "(a+b)(a+d)" "bd"
	./mygrep "(a+b)(a+d)" "aa"
	./mygrep "((a+b)a)+((c+a)d)" "aac"
	./mygrep "((a+b)a)+((c+a)d)" "ba"
	
	# Test de l'étoile de Kleene
	./mygrep "a*" "b"
	./mygrep "a*" "aaaaaaaaaaaaa"
	./mygrep "a*" "a"
	./mygrep "(a+b)*" "a"
	./mygrep "(a+b)*" "b"
	./mygrep "(a+b)*" ""
	./mygrep "a((a+b)*)" "a" 

	# Test l'exemple
	./mygrep "a(fx+db)*zx*y" "afxfxzy"
	./mygrep "a(fx+db)*zx*y" "azy"
	./mygrep "a(fx+db)*zx*y" "afxfxfxdbfxzxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxy"
	./mygrep "a(fx+db)*zx*y" "aza"

	# Test de [c1c2c3c4...ci]
	./mygrep "a+[cdr]r" "dr"
	./mygrep "a+[cdr]r" "cr"
	./mygrep "a+[cdr]r" "a"
	./mygrep "[abc][abc]" "aa"
	./mygrep "[abc][abc]" "ca"
	./mygrep "[abc][abc]" "c"
	
	# Test de E{n}
	./mygrep "a{4}" "aa"
	./mygrep "a{4}" "aaaa"
	./mygrep "a{4}" "aaaaaa"
	./mygrep "[abc]{5}" "abcbc"
	./mygrep "[abc]{5}" "aaaaa"
	./mygrep "[abc]{5}" "aaaaa"
	./mygrep "[abc]{5}a" "abcbba"