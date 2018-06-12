

import com.sun.org.apache.bcel.internal.generic.NEW;

import javax.xml.transform.Result;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class test1 {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        System.out.print("배열의 길이를 입력하세요 :");
        int n = scanner.nextInt();

        List<Integer> arr1 = new ArrayList<Integer>();
        List<Integer> arr2 = new ArrayList<Integer>();
        List<String> result = new ArrayList<String>();
        int temp = 0;
        String tempBinary = "";
        String word = "";
        System.out.print("첫번째 배열의 숫자를 연속으로 입력해주세요:");
        for(int i =0; i < n; i++){
            arr1.add(i, scanner.nextInt());
        }

        System.out.print("두번째 배열의 숫자를 연속으로 입력해주세요:" );
        for(int j =0; j < n; j++){
            arr2.add(j, scanner.nextInt());
        }

        for(int k =0; k < n; k++){
            temp = arr1.get(k) | arr2.get(k);
            tempBinary = Integer.toBinaryString(temp);
            result.add(tempBinary);
        }

        for(int p = 0; p < n; p++){
            tempBinary = result.get(p);
            word = "";
            System.out.println("이진수는 뭐게: " + tempBinary);
            for(int q = 0; q < tempBinary.length(); q++){
                if(tempBinary.charAt(q) == '1') word += '#';
                else word += ' ';
            }
            result.set(p, word);
        }

        System.out.println("배열을 출력 : " + result.toString());

    }
}
