import java.util.Scanner;

public class test3 {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        //System.out.print("셔틀 운행 횟수(n)을 입력하세요 :");
        int n = scanner.nextInt();

       // System.out.print("셔틀 운행 간격(t)을 입력하세요 :");
        int t = scanner.nextInt();

       // System.out.print("버스에 탈수있는 최대 크루 수(m)을 입력하세요 :");
        int m = scanner.nextInt();


        System.out.print("대기열에 도착하는 시간을  입력하세요:(종료는 end 입력):");
        String nation = "";
        while(inputs.size() < 2000){
            nation = scanner.next();

            if(!nation.equalsIgnoreCase("end"))
                inputs.add(nation.toLowerCase());
            else break;
        }

    }
}
