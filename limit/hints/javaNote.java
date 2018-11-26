import java.util.*;
import java.math.*;
public class javaNote
{
	static BigInteger q[] = new BigInteger[5000000]; // 定义数组的正确姿势，记得分配内存
	public static void main(String[] args) 
	{
		long currentTime = System.currentTimeMillis(); // 获取时间，单位是ms

		Scanner sc = new Scanner(System.in); // 定义输入
		int a = sc.nextInt(), b;
		System.out.println("integer = " + a); // 输出

		BigInteger x = new BigInteger("233"), y = new BigInteger("666");
		BigInteger.valueOf(1); // 将指定的表达式转化成BigInteger类型
		x.add(y); //x+y
		x.subtract(y); //x-y
		x.multiply(y); //x*y
		x.divide(y);

		x.pow(233); // x**233
		x.compareTo(y); // 比较x和y, x < y : -1, x = y : 0, x > y : 1

		BigDecimal n = new BigDecimal("233"), m = new BigDecimal("666");
		n.divide(m,a,RoundingMode.DOWN); //n/m并精确到小数点后第a位，a=0表示精确到个位，a为负数表示精确到小数点前-a+1位，可能变成科学计数法
		/*
			取整方式
			RoundingMode.CEILING：取右边最近的整数，即向正无穷取整
			RoundingMode.FLOOR：取左边最近的整数，即向负无穷取整
			RoundingMode.DOWN：向0取整
			RoundingMode.UP：远离0取整
			RoundingMode.HALF_UP:上取整的四舍五入，>=0.5会进位，<0.5会舍去，负数会先取绝对值再四舍五入再变回负数
			RoundingMode.HALF_DOWN:下取整的四舍五入，>0.5会进位，<=0.5会舍去，负数原理同上
			RoundingMode.HALF_EVEN:分奇偶的四舍五入，>0.5会进位，<0.5会舍去，=0.5会向最近的偶数取整，如2.5->2，(-2.5)->(-2)
		*/
		Math.max(a, b);//取大
		Math.min(a, b);//取小
		Math.PI;//pi

		HashSet<BigInteger> hash = new HashSet<BigInteger>(); // hash table
		hash.contains(x); // hash table中是否有a，有则返回true，反之返回false
		hash.add(x); // 把x加进hash table
		hash.remove(x); // 从hash table中删去x

		Arrays.sort(arr, 1, n+1); // arr 是需要排序的数组，后两个参数分别是排序的起始位置和结束位置+1，还可以有第四个参数是比较函数 
		// Arrays.sort(arr, a, b, cmp) = sort(arr+a, arr+b, cmp)
	}
	
	public static BigInteger sqrt (BigInteger x) {
	if (x.equals (BigInteger.ZERO) || x.equals (BigInteger.ONE)) return x;
	BigInteger d = BigInteger.ZERO.setBit (x.bitLength () / 2);
	BigInteger d2 = d;
	for (; ; ) {
		BigInteger y = d.add (x.divide (d)).shiftRight (1);
		if (y.equals (d) || y.equals (d2)) return d.min (d2);
		d2 = d; d = y; } }
}