#include <vector>
#include <utility>
#include <iostream>


float auc(std::vector<float> true_positive_rate, std::vector<float> false_positive_rate){
  int size = true_positive_rate.size();
  float q1,q2,p1,p2;
  q1 = false_positive_rate[0];
  q2 = true_positive_rate[0];
  float area = 0.0;
  for(int i=1; i < size; ++i){
    p1 = false_positive_rate[i];
    p2 = true_positive_rate[i];
    area += (p2 + q2) * (p1 - q1) / 2;
    q1 = p1;
    q2 = p2;   
  }
  return area;
}


float rocAucScore(std::vector<std::pair<float,int> > data){
  std::vector<float> true_positive_rate;
  std::vector<float> false_positive_rate;

  sort(data.begin(),
  	data.end(),
  	[](const std::pair<float,int> &a, 
  		const std::pair<float,int>& b){
  		return a.first > b.first;
  	});
  int L = data.size();
  int count_positive = 0;
  int count_negative = 0;

  for (int j = 0; j < data.size(); j++) {
    if (data[j].second==1){
		++count_positive;
	}else {
		++count_negative;
  	}
  }

  double count_false_positive = 0;
  double count_true_positive = 0;
  double score_prev = -std::numeric_limits<double>::infinity();
  
  for (int i = 0; i < L; i++) {
    double score = data[i].first;
    int label = data[i].second;
    if (score != score_prev){

		true_positive_rate.push_back(count_true_positive/count_positive);
		false_positive_rate.push_back(count_false_positive/count_negative);
		score_prev = score;
    }
    if(label==1){
		++count_true_positive;
    }else{
		++count_false_positive;
    }
  }

  true_positive_rate.push_back(1);
  false_positive_rate.push_back(1);

  return auc(true_positive_rate, false_positive_rate);
}

int main(){
	std::vector<std::pair<float,int> > data;
	data.emplace_back(0.1, 0);
	data.emplace_back(0.4, 0);
	data.emplace_back(0.35, 1);
	data.emplace_back(0.8, 1);
	std::cout<<rocAucScore(data)<<std::endl;
	return 0;
}
