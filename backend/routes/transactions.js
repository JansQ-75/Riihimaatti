const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');
const bank_account = require('../models/bank_account_model');
const { checkAdmin } = require('../authentication');

router.get('/', checkAdmin, function (req, res) {
  transaction.getAll((err, result) => {
    if (err) {
      res.json(err);
    } else {
      res.json(result);
    }
  });
});

// Show transactions
router.get('/:idbank_account/:offsetValue',
  bank_account.validateAccountIdAccess, function (request, response) {
    transaction.showTransactions(
      request.params.idbank_account, request.params.offsetValue, function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result[0]);
      }
    });
  });

// Make withdrawal
router.get('/:account_type/:idbank_account/:idcard/:withdrawal', bank_account.validateAccountIdAccess, function (request, response) {
  transaction.makeWithdrawal(request.params.account_type, request.params.idbank_account, request.params.idcard, request.params.withdrawal,
    function (err, result) {
      if (err) {
        response.json(err);
      } else {
        response.json(result.affectedRows);
      }
    },
  );
});

// Transactions by id
router.get('/:idbank_account', bank_account.validateAccountIdAccess, function (request, response) {
  transaction.transactionsById(request.params.idbank_account, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});


 // Delete transactions, admin access 
router.delete('/:idtransaction', checkAdmin, function (request, response) {
  transaction.delete(request.params.idtransaction, function (err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result.affectedRows);
    }
  });
});

// Update transactions
router.put('/:idtransaction', checkAdmin,
  function (request, response) {
    transaction.update(request.params.idtransaction, request.body,
      function (err, result) {
        if (err) {
          response.json(err);
        } else {
          response.json(result.affectedRows);
        }
      },
    );
  },
);

module.exports = router;
