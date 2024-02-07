pragma solidity 0.5.16;

import "./Store.sol";

contract Escrow {
    address owner;
    address buyer;
    address seller;
    bytes32 productId;
    uint createdAt = now;
    uint public buyerOk;
    uint public sellerOk;

    modifier onlyParticipant {
        require(msg.sender == buyer || msg.sender == seller);
        _;
    }

    constructor (address _buyer, address _seller, bytes32 _productId) public payable {
        require(msg.value > 0);
        owner = msg.sender;
        buyer = _buyer;
        seller = _seller;
        productId = _productId;
    }

    function accept() public onlyParticipant {
        Store store = Store(owner);

        if (msg.sender == seller && sellerOk == 0) {
            sellerOk = now;
            store.updateProductStatus(productId, Store.ProductStatus.Shipping);
        } else if (msg.sender == buyer && buyerOk == 0) {
            buyerOk = now;
            store.updateProductStatus(productId, Store.ProductStatus.Sold);
        }

        if (buyerOk != 0 && sellerOk != 0) {
            address payable sellerPayable = address(uint160(seller));
            sellerPayable.transfer(address(this).balance);
        }
    }

    function reject() public onlyParticipant {
        Store store = Store(owner);
        store.updateProductStatus(productId, Store.ProductStatus.Available);
        address payable buyerPayable = address(uint160(buyer));
        buyerPayable.transfer(address(this).balance);
    }
}
