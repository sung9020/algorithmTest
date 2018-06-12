import java.util.*;

public class test2 {
    public static void main(String[] args) {

        /* 오류 해결중 20180612 */
        Scanner scanner = new Scanner(System.in);
        System.out.print("캐시 크기를 입력하세요 :");
        int size = scanner.nextInt();
        List<String> inputs = new ArrayList<String>();

        System.out.print("처리를 원하는 나라를 연속으로 입력해주세요(종료는 end 입력):");
        String nation = "";
        while(inputs.size() < 100000){
            nation = scanner.next();

            if(!nation.equalsIgnoreCase("end"))
            inputs.add(nation);
            else break;
        }

        List<String> caches = new LinkedList<String>();
        Stack<Integer> pages = new Stack<Integer>();
        int page = 0;
        int result = 0;
        for(String input : inputs){
            if(caches.size() < size) {
                caches.add(input);
                if(!pages.contains(caches.indexOf(input)))
                    pages.push(caches.indexOf(input));
                else {
                    pages.remove(caches.indexOf(input));
                    pages.push(caches.indexOf(input));
                }
                result += 5;
            }
            else{
                if(caches.contains(input))
                {
                    pages.remove(caches.indexOf(input));
                    pages.push(caches.indexOf(input));
                    result += 1;
                }else{

                    page = pages.get(0);
                    caches.set(page,input);
                    pages.remove(page);
                    pages.push(page);
                    result += 5;
                }


            }

        }
        System.out.println("처리 시간:" + result);
    }
}
