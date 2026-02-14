#include <string>
#include <cctype> // for isalpha
#include <stdexcept>

#include "Expression.hpp"

/* Default constructor */
Expression::Expression() 
{}

/* Public member functions */
void Expression::setFromPrefix(const std::string &pre)
{
  // TODO: check format
  //chack if postfix and throw error if it isn'y
  if (!isPre(pre)){
    throw std::invalid_argument("Invalid prefix expression");
  }

  // TODO: store prefix and postfix forms
  //set pre to prefix
  prefix = pre;
  //clear postfix and turn pre to postfix and save it
  postfix.clear();
  prefixToPostfix(pre, postfix);
}

void Expression::setFromPostfix(const std::string &post)
{
  // TODO: check format
  //test if postFix, thorw error if it is
  if(!isPost(post)){
    throw std::invalid_argument("Invalid postfix expression");
  }

  // TODO: store prefix and postfix forms
  //set post to postfix
  postfix = post;
  //clear pre and turn post ot prefix
  prefix.clear();
  postfixToPrefix(post, prefix);
}

std::string Expression::getPrefix() const
{
    // TODO
    //return the variable
    return prefix;
}

std::string Expression::getPostfix() const
{
    // TODO
    //return the variable
    return postfix;
}

/* Private member functions */
void Expression::prefixToPostfix(const std::string &prefix, std::string &postfix) const {
  // from textbook section 6.3.3
  int end1, end2;
  char first_char = prefix[0];
  if(isOperator(first_char)) {
    // recursively parse expression
    end1 = endPre(prefix,1);
    end2 = endPre(prefix,end1+1);
    // operand/subexpression
    prefixToPostfix(prefix.substr(1,end1), postfix);
    // operand/subexpression
    prefixToPostfix(prefix.substr(end1+1,end2-end1), postfix);
    // operator
    postfix += first_char;
  } else {
    // operand
    postfix += first_char;
  }
}

void Expression::postfixToPrefix(const std::string &postfix, std::string &prefix) const {

  // TODO: recursive function
  //one operand
  if(postfix.size() == 1) {
    prefix+=postfix[0];
    return;
  }
  //operator is at back
  char op = postfix.back();
  //start index of rihgt
  int rightStart = endPost(postfix, (int)postfix.size() -2);
  //start index of left
  int leftStart = endPost(postfix, rightStart - 1);

  //make each side
  std::string left = postfix.substr(leftStart, rightStart - leftStart);
  std::string right = postfix.substr(rightStart, postfix.size() - 1 - rightStart);

  //prefix has operator first
  prefix += op;
  postfixToPrefix(left, prefix);
  postfixToPrefix(right, prefix);

}


