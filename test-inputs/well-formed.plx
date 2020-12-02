fun alpha(a) {
	return a + 4
}

fun beta(a, b) {
	return a or b
}

var result1 = alpha(10)
var result2 = beta(true, false)
if (result1 >= result2) {
	print "Success!"
}
print result1
print result2
