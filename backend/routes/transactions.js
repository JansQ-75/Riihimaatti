const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

/* GET all transactions
  ONLY FOR INITIAL DB DEBUG PURPOSES
  MUST BE DELETED, SOON(TM)
 */
router.get('/', function (req, res, next) {
  transaction.getAll((err, result) => {
    if (err) {
      res.json(err);
    } else {
      res.json(result);
    }
  });
});


//td
router.get('/:transaction_date', function (request, response) {
  transaction.getTransaction_date(request.params.transaction_date, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

//wm
router.put('/:transaction', function (request, response) {
  balance.update(request.params.transaction, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

//p10
router.get('/:transaction', function (request, response) {
  transaction.showPreviousTransactions(request.params.transaction, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

//n10
router.get('/:transaction', function (request, response) {
  transaction.showNextTransactions(request.params.transaction, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

router.post('/', function (request, response) {
  transaction.makeDebitWithdrawal(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

router.post('/', function (request, response) {
  transaction.makeCreditWithdrawal(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

router.post('/', function (request, response) {
  transaction.atm_transactions(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

module.exports = router;
