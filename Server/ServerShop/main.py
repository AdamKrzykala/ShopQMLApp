# This Python file uses the following encoding: utf-8
from flask import Flask, request

app = Flask(__name__)

shopStore = list()
shopStore.append({'id': 1, 'name': "Chleb", "price": 100, "weight": 100})
shopStore.append({'id': 2, 'name': "Maslo", "price": 200, "weight": 200})
shopStore.append({'id': 3, 'name': "Szynka", "price": 300, "weight": 300})
shopStore.append({'id': 4, 'name': "Ser", "price": 400, "weight": 400})
shopStore.append({'id': 5, 'name': "Woda", "price": 500, "weight": 500})


@app.route('/getProducts')
def getProducts():
    responseValue = {'products': []}
    for shopElementItem in shopStore:
        responseValue['products'].append(shopElementItem)
    return responseValue


@app.route('/order_request', methods=['GET', 'POST'])
def calculateOrder():
    price = request.args.get('price')
    if price:
        return {'result': float(price) * 1.23}
    return {'result': 0}


@app.errorhandler(404)
def errorHandler(errno):
    return f"Error occured + {errno}"


if __name__ == "__main__":
    app.run(debug=True)
