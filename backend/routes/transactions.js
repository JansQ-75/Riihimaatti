const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

/* GET all transactions
  ONLY FOR INITIAL DB DEBUG PURPOSES
  MUST BE DELETED, SOON(TM)
 */
router.get('/', function (req, res, next) {
  transaction.getAll((err, result) => {
    res.send(result);
  });
});


module.exports = router;
