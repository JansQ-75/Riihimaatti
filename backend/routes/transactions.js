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
router.get('/transaction_date', function (request, response) {
  transaction.getTransaction_date(request.params.transaction_date, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

//wm
router.put('/transaction', function (request, response) {
  balance.update(request.params.transaction, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

//showTransacs
router.get('/gettransaction/', function (request, response) {
  transaction.showTransactions(request.params.transaction, request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

router.post('/:account_type', function (request, response) {
  transaction.makeWithdrawal(
    request.params.account_type,
    request.body,
    function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result.affectedRows);
      }
    },
  );
});

router.get('/', function (request, response) {
  transaction.atm_transactions(request.body, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

module.exports = router;
