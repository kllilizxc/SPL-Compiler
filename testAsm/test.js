var gcd = function(a,b)
{
	if(b == 0)
		return a;
	else
		return gcd(b, 0);
		
};

var ans = gcd(9,36) * gcd(3,6);
console.log(ans); 
