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
  if (!isPre(pre)){
    throw std::invalid_argument("Invalid prefix expression");
  }

  // TODO: store prefix and postfix forms
  prefix = pre;
  postfix.clear();
  prefixToPostfix(pre, postfix);
}

void Expression::setFromPostfix(const std::string &post)
{
  // TODO: check format
  if(!isPost(post)){
    throw std::invalid_argument("Invalid postfix expression");
  }

  // TODO: store prefix and postfix forms
  postfix = post;
  postfix.clear();
  prefixToPostfix(post, prefix);
}

std::string Expression::getPrefix() const
{
    // TODO
    return prefix;
}

std::string Expression::getPostfix() const
{
    // TODO
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

}


